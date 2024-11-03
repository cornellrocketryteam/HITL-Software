#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

// function that splits a string based on a delimeter
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    std::string current;
    for (char c : str) {
        if (c == delimiter) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    if (!current.empty()) {
        result.push_back(current);
    }
    return result;
}

int main() {
  std::string filename{"data/past_data_1.csv"};
  std::ifstream input{filename};

  if (!input.is_open()) {
    std::cerr << "Couldn't read file: " << filename << "\n";
    return 1; 
  }

  std::vector<std::vector<std::string>> csvRows;

  for (std::string line; std::getline(input, line);) {
    std::istringstream ss(std::move(line));
    std::vector<std::string> row;
    if (!csvRows.empty()) {
       // We expect each row to be as big as the first row
      row.reserve(csvRows.front().size());
    }
    // std::getline can split on other characters, here we use ','
    for (std::string value; std::getline(ss, value, ',');) {
      row.push_back(std::move(value));
    }
    csvRows.push_back(std::move(row));
  }

  // Print out our table
  for (const std::vector<std::string>& row : csvRows) {
    for (const std::string& value : row) {
      std::cout << std::setw(10) << value;
    }
    std::cout << "\n";
  }
}



