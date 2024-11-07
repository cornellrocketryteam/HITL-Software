/**
 * @file main.cpp
 * @author cy452
 * 
 * @brief The entry point for the program
 */

#include <cstdio>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/i2c_slave.h"
#include "pins.hpp"
#include "tusb.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "constants.hpp"


// define I2C addresses of slave (rn it's the altimeter's)
#define I2C0_SLAVE_ADDR 0x77

#define I2C_PORT i2c0

#define I2C_BAUDRATE 400000 // 100 kHz

// define base address of I2C controller hardware
// #define I2C0_BASE 0x40044000

// // C++ program for implementation of Lagrange's Interpolation
// using namespace std;

// To represent a data point corresponding to x and y = f(x)
struct Data
{
    int x, y;
};

// function to interpolate the given data points using Lagrange's formula
// xi corresponds to the new data point whose value is to be obtained
// n represents the number of known data points
float interpolate(Data f[], int xi, int n)
{
    float result = 0; // Initialize result

    for (int i=0; i<n; i++)
    {
        // Compute individual terms of above formula
        float term = f[i].y;
        for (int j=0;j<n;j++)
        {
            if (j!=i)
                term = term*(xi - f[j].x)/float(f[i].x - f[j].x);
        }

        // Add current term to result
        result += term;
    }

    return result;
}

// The slave implements a 256 byte memory. To write a series of bytes, the master first
// writes the memory address, followed by the data. The address is automatically incremented
// for each byte transferred, looping back to 0 upon reaching the end. Reading is done
// sequentially from the current memory address.
static struct
{
    uint8_t mem[256];
    uint8_t mem_address;
    bool mem_address_written;
} context;


// Our handler is called from the I2C ISR, so it must complete quickly. Blocking calls /
// printing to stdio may interfere with interrupt handling.
static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    static uint8_t response_byte = 0x50;
    static uint8_t register_address = 0x0;

    bool chip_id_data = false;

    switch (event) {
    case I2C_SLAVE_RECEIVE: // master has written some data
        i2c_read_raw_blocking(i2c, &register_address, 1);

        switch(register_address){
            case 0x0:
                chip_id_data = true;
                break;
            
            default:
                break;

        }

        break;
    case I2C_SLAVE_REQUEST: // master is requesting data
        if (I2C_SLAVE_REQUEST)
        {
            if (chip_id_data)
            {i2c_write_raw_blocking(i2c, &response_byte, 1);}
        }
        break;
    case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
        context.mem_address_written = false;
        break;
    default:
        break;
    }
}

static void setup_slave() {
    gpio_init(GPIO_SDA0);
    gpio_set_function(GPIO_SDA0, GPIO_FUNC_I2C);
    gpio_pull_up(GPIO_SDA0);

    gpio_init(GPIO_SCK0);
    gpio_set_function(GPIO_SCK0, GPIO_FUNC_I2C);
    gpio_pull_up(GPIO_SCK0);

    i2c_init(i2c0, I2C_BAUDRATE);
    // configure I2C0 for slave mode
    i2c_slave_init(i2c0, I2C0_SLAVE_ADDR, &i2c_slave_handler);
}

// Write 1 byte to the specified register
int reg_write(  i2c_inst_t *i2c, 
                const uint addr, 
                const uint8_t reg, 
                uint8_t *buf,
                const uint8_t nbytes) {

    int num_bytes_read = 0;
    uint8_t msg[nbytes + 1];

    // Check to make sure caller is sending 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Append register address to front of data packet
    msg[0] = reg;
    for (int i = 0; i < nbytes; i++) {
        msg[i + 1] = buf[i];
    }

    // Write data to register(s) over I2C
    i2c_write_blocking(i2c, addr, msg, (nbytes + 1), false);

    return num_bytes_read;
}

// Read byte(s) from specified register. If nbytes > 1, read from consecutive
// registers.
int reg_read(  i2c_inst_t *i2c,
                const uint addr,
                const uint8_t reg,
                uint8_t *buf,
                const uint8_t nbytes) {

    int num_bytes_read = 0;

    // Check to make sure caller is asking for 1 or more bytes
    if (nbytes < 1) {
        return 0;
    }

    // Read data from register(s) over I2C
    i2c_write_blocking(i2c, addr, &reg, 1, true);
    num_bytes_read = i2c_read_blocking(i2c, addr, buf, nbytes, false);

    return num_bytes_read;
}

int main() {
    stdio_init_all();

    // turn on LED
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 1);

    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / slave_mem_i2c example requires a board with I2C pins
        puts("Default I2C pins were not defined");
        return 0;
    #else
        puts("\nI2C slave example");

        setup_slave();
    #endif

    // setup_slave();

    // // Not sure if this is necessary
    // while (!tud_cdc_connected()) {
    // sleep_ms(500);
    // }
    // printf("Connected\n");

    while (true) {
        // Blink LED
        printf("Blinking!\r\n");
        gpio_put(LED, true);
        sleep_ms(1000);
        gpio_put(LED, false);
        sleep_ms(1000);

        

    }

    return 0;
}