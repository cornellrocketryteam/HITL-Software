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
#include <vector>
#include "constants.hpp"
#include "csv_parser.cpp"
#include <cmath>


// define I2C addresses of slave (rn it's the altimeter's)
#define I2C0_SLAVE_ADDR 0x77

#define I2C_PORT i2c0

#define I2C_BAUDRATE 400000 // 100 kHz

const float Data_1[2432] = {1.374814, 1.269207, 1.359224, 1.013744, 0.957422, 0.792985, 0.809579, 0.670790, 0.581282, 0.645144, 0.685875, 0.670790, 0.424393, 0.253427, 0.677830, 0.931776, 0.760802, 0.383662, 0.719567, 0.219737, 0.097046, 0.399250, 0.424393, 0.097046, 0.342932, 0.097046, 0.481214, 0.179007, 0.432941, 0.350475, 0.752253, 0.424393, 0.677830, 0.383662, 0.711521, 0.604413, -0.804488, 3.227126, 2.611999, 2.595905, 2.923833, 4.079713, 5.260372, 5.752897, 6.679653, 8.047800, 9.327047, 11.459642, 13.174290, 15.036255, 17.072311, 19.000963, 22.711185, 25.652491, 29.027752, 32.430332, 35.759354, 39.392780, 42.297909, 46.112404, 49.216942, 52.970802, 57.549625, 62.204823, 66.469910, 71.803474, 76.142403, 81.053223, 87.736435, 93.637489, 99.969353, 107.581223, 113.873291, 120.204277, 128.120636, 134.016647, 142.545044, 147.259384, 155.113205, 163.650787, 171.295166, 179.387680, 186.889572, 192.846741, 202.868942, 211.211395, 220.994034, 230.630646, 241.425354, 251.456528, 261.528870, 269.892395, 279.976501, 288.228271, 299.851257, 310.722565, 324.445282, 336.715149, 348.001221, 357.410767, 369.224335, 381.247070, 391.765717, 404.026459, 415.649078, 425.319550, 438.425903, 449.538086, 463.251007, 476.316711, 491.669159, 503.521423, 515.162231, 528.504028, 540.865540, 554.161133, 566.415466, 577.399231, 591.120178, 607.505005, 626.305786, 639.523132, 653.588196, 665.621704, 681.684998, 697.558289, 711.390747, 725.334717, 741.664246, 757.496582, 772.908508, 789.845520, 805.880371, 820.921631, 835.940430, 849.915955, 865.243713, 881.394592, 898.864685, 916.630127, 932.417297, 948.268066, 960.781067, 977.438965, 992.191650, 1006.873779, 1022.071777, 1037.475586, 1052.808472, 1066.992188, 1082.728882, 1095.673462, 1113.008789, 1128.999390, 1144.245239, 1156.309082, 1168.295532, 1182.453003, 1198.233154, 1214.171997, 1226.920044, 1242.903564, 1257.856812, 1271.671753, 1284.528931, 1299.178101, 1310.073364, 1324.418701, 1342.373779, 1354.763916, 1359.980103, 1367.180176, 1381.926758, 1399.092773, 1420.836060, 1440.040405, 1457.532471, 1469.180420, 1476.347534, 1486.202759, 1508.218994, 1521.292480, 1532.140259, 1545.726318, 1560.361938, 1576.853027, 1591.413696, 1602.581543, 1608.154175, 1619.100342, 1636.981079, 1652.803711, 1665.383911, 1677.001221, 1692.171997, 1703.056396, 1716.440430, 1731.208862, 1740.516846, 1751.984009, 1763.387207, 1773.860596, 1789.548706, 1802.854004, 1813.270996, 1825.552490, 1839.248535, 1850.659546, 1862.294312, 1874.635132, 1886.794678, 1898.842896, 1909.577026, 1921.728882, 1934.448730, 1945.444580, 1956.057251, 1967.496094, 1980.334961, 1992.211426, 2003.295288, 2015.707886, 2026.169312, 2037.938477, 2050.830078, 2061.628418, 2071.698730, 2083.833740, 2095.694336, 2106.025879, 2117.020020, 2127.552246, 2138.859375, 2149.991455, 2160.127197, 2170.438232, 2180.124268, 2190.717529, 2201.949707, 2213.883789, 2224.743652, 2234.054443, 2242.159424, 2251.247559, 2260.874268, 2273.999268, 2286.646240, 2299.763916, 2308.381836, 2317.274658, 2327.698975, 2337.810303, 2348.959229, 2360.584229, 2369.852539, 2377.154297, 2385.680176, 2395.249268, 2407.238281, 2418.517090, 2429.117676, 2439.936768, 2449.123047, 2459.998779, 2469.948975, 2479.771729, 2488.803955, 2498.086914, 2507.275635, 2516.681152, 2525.572998, 2533.879883, 2543.326416, 2554.602783, 2564.492920, 2573.550049, 2583.139404, 2592.195801, 2601.907471, 2611.124756, 2620.014648, 2628.754150, 2638.640381, 2647.236572, 2656.312256, 2665.462402, 2675.157959, 2683.713867, 2693.533936, 2701.467285, 2709.512939, 2717.211670, 2725.570068, 2734.436523, 2742.583496, 2751.712402, 2759.316406, 2768.428467, 2778.104980, 2787.911377, 2796.371582, 2805.280762, 2814.359619, 2822.196045, 2830.037598, 2839.355469, 2847.297363, 2855.224609, 2862.497559, 2869.267090, 2877.287109, 2885.074707, 2893.673828, 2902.746826, 2911.340332, 2919.285400, 2927.011963, 2935.274658, 2943.294678, 2951.189941, 2960.104736, 2966.816406, 2975.339600, 2982.375000, 2990.786621, 2999.322021, 3006.687256, 3013.878906, 3021.884521, 3029.394043, 3036.578857, 3044.058105, 3052.050537, 3060.006592, 3067.576416, 3075.453125, 3082.476074, 3089.041016, 3096.744385, 3103.146484, 3111.224121, 3119.505371, 3126.008545, 3132.876465, 3139.834473, 3146.548584, 3153.932861, 3160.935791, 3167.962402, 3175.171875, 3183.115234, 3189.322021, 3196.795166, 3204.164062, 3211.061279, 3217.148193, 3224.169189, 3229.873047, 3236.393799, 3241.847900, 3249.024414, 3255.222900, 3261.027100, 3267.628174, 3274.595459, 3281.541992, 3289.002441, 3296.439941, 3302.949951, 3310.599609, 3316.067139, 3322.363281, 3328.663086, 3334.710938, 3340.989990, 3347.131104, 3353.475342, 3358.912109, 3364.922852, 3371.277832, 3376.412109, 3382.175781, 3388.770752, 3394.170410, 3400.345703, 3406.925049, 3414.024170, 3420.153564, 3425.887451, 3431.966309, 3437.447021, 3442.760010, 3447.959717, 3453.940186, 3459.778320, 3465.071533, 3470.169434, 3475.959717, 3481.208496, 3486.314941, 3491.998779, 3497.655762, 3502.972168, 3508.175293, 3513.036621, 3519.345459, 3525.686035, 3531.857178, 3537.655273, 3542.997559, 3547.989990, 3553.504395, 3558.909424, 3563.798096, 3569.325195, 3574.300537, 3579.627197, 3584.352295, 3589.424805, 3595.402100, 3599.689209, 3604.657959, 3609.677734, 3613.449951, 3618.097168, 3623.069580, 3626.879883, 3632.352539, 3637.184082, 3641.729736, 3646.826904, 3651.937500, 3656.105957, 3661.177979, 3666.120605, 3670.529785, 3674.712891, 3678.884766, 3683.424316, 3688.221924, 3693.198242, 3697.856689, 3702.575684, 3706.581787, 3710.873291, 3715.861572, 3720.937012, 3725.115967, 3729.697754, 3733.163330, 3737.689209, 3741.487549, 3746.110352, 3750.015381, 3754.252441, 3758.260498, 3763.069824, 3766.394775, 3770.562012, 3775.097656, 3778.163086, 3781.766113, 3786.390869, 3789.546143, 3793.170166, 3796.582275, 3799.860840, 3804.476807, 3807.731689, 3811.217529, 3815.787842, 3819.669922, 3822.605957, 3826.865234, 3830.691162, 3834.468506, 3837.639648, 3840.931641, 3844.753662, 3848.657227, 3851.882080, 3855.119141, 3858.006836, 3861.365967, 3865.194580, 3868.856689, 3871.629150, 3874.572266, 3878.167480, 3880.990967, 3884.754150, 3887.857422, 3890.563965, 3893.863281, 3897.075928, 3900.136475, 3902.786865, 3905.630371, 3908.270508, 3911.791992, 3914.626953, 3917.136230, 3920.299316, 3923.293457, 3925.768555, 3928.196533, 3931.169922, 3933.985352, 3936.354980, 3939.705078, 3942.003662, 3945.150391, 3947.208008, 3950.078125, 3952.439697, 3955.528564, 3958.278564, 3960.255127, 3962.024414, 3964.498535, 3967.519287, 3969.144775, 3971.656494, 3974.485352, 3976.220703, 3978.516113, 3980.641602, 3983.314941, 3985.198242, 3987.240479, 3989.672852, 3991.399170, 3993.758301, 3995.643555, 3998.127197, 4000.220215, 4001.998779, 4004.407959, 4006.552002, 4008.111084, 4010.268311, 4012.851807, 4014.351807, 4015.997314, 4018.314453, 4019.791016, 4021.400635, 4023.451416, 4024.611572, 4026.780762, 4028.466064, 4030.104248, 4031.579102, 4032.998291, 4034.670410, 4036.037842, 4037.870605, 4039.046143, 4040.560059, 4041.514648, 4043.335449, 4044.449707, 4046.124023, 4046.956543, 4048.241211, 4050.015137, 4051.055420, 4052.401855, 4053.235107, 4055.118652, 4055.829834, 4056.907471, 4058.301758, 4059.258057, 4060.459717, 4061.770508, 4062.711914, 4063.339355, 4064.673340, 4065.690918, 4066.793945, 4067.958740, 4068.326660, 4069.100098, 4069.897705, 4070.318115, 4071.529297, 4071.982422, 4072.641602, 4073.906982, 4074.581543, 4075.440186, 4075.845703, 4076.912109, 4077.280518, 4077.710449, 4077.832520, 4078.752930, 4079.305664, 4079.366943, 4080.210938, 4080.471924, 4081.331787, 4081.783691, 4082.067383, 4082.252441, 4083.049805, 4082.742432, 4082.904053, 4083.295410, 4083.725586, 4083.211182, 4083.579102, 4084.094238, 4084.094238, 4084.032715, 4084.339355, 4084.570557, 4084.292236, 4083.971436, 4084.094238, 4084.400635, 4084.155029, 4084.192871, 4083.418457, 4083.310547, 4083.357666, 4083.234131, 4082.766846, 4082.620361, 4082.213867, 4081.960449, 4081.039795, 4081.161865, 4080.878174, 4080.202637, 4080.226074, 4078.744629, 4078.975830, 4078.361572, 4078.139404, 4077.380615, 4076.620361, 4075.662354, 4075.332520, 4075.194580, 4074.166260, 4073.807129, 4073.047852, 4072.150635, 4071.330811, 4070.410400, 4069.628662, 4069.001709, 4068.341064, 4067.137695, 4066.379883, 4065.323730, 4064.733887, 4063.315918, 4062.703613, 4061.500977, 4060.238770, 4058.523438, 4057.863770, 4056.762451, 4055.829834, 4054.764893, 4053.272949, 4052.147705, 4051.338135, 4049.624512, 4048.057617, 4046.933105, 4045.686523, 4044.547852, 4043.301514, 4041.575684, 4040.597900, 4038.839355, 4037.847168, 4036.296875, 4035.112549, 4033.096191, 4032.092041, 4029.968506, 4028.394531, 4026.733154, 4025.207764, 4023.841064, 4022.194336, 4020.509277, 4018.205078, 4016.643555, 3986.852295, 4015.705811, 4010.914795, 4008.757568, 4007.783691, 4006.321777, 4001.706787, 4000.452637, 4000.293945, 3993.407227, 3992.471191, 3986.986572, 3983.607666, 3981.067871, 3977.606201, 3976.173584, 3974.412598, 3970.723145, 3969.715820, 3971.074707, 3969.995361, 3971.172119, 4013.988037, 3960.837646, 3962.522461, 3959.212891, 3958.715088, 3952.450928, 3945.634033, 3941.228760, 3940.417969, 3938.168457, 3936.849365, 3932.872070, 3929.983154, 3926.635498, 3924.534668, 3920.717773, 3920.067627, 3916.083984, 3913.416992, 3910.414062, 3907.712891, 3904.759521, 3901.614990, 3898.228027, 3896.265869, 3892.968018, 3891.644043, 3888.115967, 3885.928467, 3886.024414, 3873.571289, 3910.825195, 3938.785400, 3967.980225, 3983.704346, 3986.463379, 3995.791016, 3957.406494, 3982.719727, 3955.419189, 3973.842041, 3953.116943, 3946.022217, 3929.586182, 3904.618652, 3920.008545, 3887.747314, 3887.446533, 3878.908936, 3883.838135, 3881.157227, 3891.923584, 3883.056152, 3915.664307, 3894.933350, 3953.020264, 3908.813477, 3939.597656, 3925.466553, 3920.636475, 3916.944092, 3877.780762, 3907.114990, 3888.112305, 3878.216309, 3889.265625, 3857.706787, 3849.725098, 3866.850830, 3848.970947, 3858.081543, 3860.370850, 3821.700439, 3852.985840, 3823.766113, 3816.231201, 3817.246826, 3794.616699, 3823.886475, 3801.801758, 3795.348145, 3807.330078, 3789.843262, 3814.942871, 3806.504150, 3797.527344, 3815.924316, 3836.782227, 3793.561523, 3820.641602, 3823.918213, 3792.123291, 3799.042969, 3796.888428, 3771.191162, 3794.454834, 3792.547852, 3775.190918, 3780.168701, 3782.370117, 3758.719482, 3786.051270, 3765.658203, 3757.881592, 3768.458008, 3734.983887, 3766.226074, 3752.185791, 3746.653564, 3753.177002, 3725.516113, 3753.821777, 3730.392822, 3738.621826, 3726.843018, 3733.680908, 3730.925781, 3726.606201, 3727.697021, 3722.525879, 3719.714844, 3722.263672, 3702.123291, 3715.703125, 3699.847656, 3718.953369, 3688.882812, 3708.346436, 3700.824707, 3682.724609, 3705.335205, 3691.718994, 3681.697021, 3706.221680, 3679.702637, 3675.465088, 3681.259277, 3670.752930, 3654.301025, 3677.871338, 3668.583496, 3654.743408, 3664.461914, 3668.492188, 3653.003174, 3652.421875, 3645.380859, 3642.033203, 3642.944824, 3639.095703, 3640.540039, 3639.895752, 3637.311523, 3645.727051, 3633.534668, 3612.409668, 3600.286377, 3604.697021, 3612.377930, 3608.786377, 3603.003418, 3604.081055, 3613.813232, 3597.336426, 3588.675781, 3603.551514, 3599.697998, 3589.841797, 3607.995361, 3588.649170, 3572.855469, 3588.002441, 3579.000732, 3588.410156, 3572.098389, 3573.150879, 3564.216064, 3570.701660, 3566.251953, 3563.285889, 3567.854248, 3565.697998, 3550.500732, 3570.061279, 3546.288574, 3561.858887, 3540.922119, 3548.208008, 3551.053955, 3530.973877, 3547.244141, 3541.850098, 3525.819824, 3537.727051, 3529.814941, 3516.205078, 3529.870117, 3521.646240, 3501.859619, 3515.333984, 3522.024658, 3498.798584, 3499.409424, 3495.909668, 3503.478271, 3501.340088, 3480.645264, 3485.695801, 3495.970459, 3497.991699, 3485.692871, 3477.476318, 3482.435547, 3494.815674, 3483.789551, 3476.669922, 3467.996826, 3472.403809, 3477.592529, 3456.288086, 3456.144531, 3455.109863, 3459.134521, 3447.635986, 3446.083496, 3443.324707, 3451.745605, 3441.402588, 3435.976318, 3432.046387, 3435.689941, 3437.498047, 3428.775879, 3420.062256, 3423.414795, 3428.230469, 3432.303467, 3410.983887, 3406.748291, 3403.659668, 3409.008301, 3409.609863, 3403.459717, 3396.082520, 3399.197754, 3385.769531, 3377.237061, 3375.440918, 3383.058105, 3350.404297, 3348.669922, 3349.579590, 3339.344971, 3335.537842, 3337.527100, 3327.759033, 3319.872070, 3323.816162, 3332.614014, 3335.027100, 3335.567871, 3337.412842, 3352.566650, 3359.824951, 3360.536621, 3356.750488, 3351.458008, 3345.542236, 3354.643799, 3349.125000, 3343.751221, 3349.295654, 3319.364502, 3337.755127, 3347.077881, 3331.989990, 3337.499756, 3308.143066, 3325.548096, 3316.756592, 3310.295898, 3319.705566, 3309.672119, 3310.124512, 3302.253662, 3307.945801, 3289.413574, 3319.479248, 3305.368164, 3294.416992, 3283.931885, 3298.717529, 3297.643555, 3282.546387, 3273.228760, 3273.257324, 3248.457275, 3255.526123, 3254.879395, 3245.192383, 3230.262939, 3223.946045, 3218.553467, 3217.714844, 3211.991943, 3211.570312, 3214.068359, 3216.532959, 3216.734619, 3219.874268, 3222.769531, 3225.967285, 3224.675537, 3246.910156, 3261.134521, 3258.937988, 3253.587646, 3241.649902, 3219.233154, 3215.807617, 3214.546143, 3220.160400, 3212.499512, 3208.020752, 3193.113525, 3169.721680, 3156.436768, 3144.646973, 3142.637207, 3139.356201, 3138.132080, 3139.159668, 3141.254639, 3140.585693, 3139.104004, 3136.371582, 3136.133301, 3139.826904, 3145.508057, 3149.137939, 3151.165527, 3164.495605, 3182.237793, 3192.531006, 3198.327393, 3192.198486, 3176.235107, 3168.385010, 3159.315186, 3162.246094, 3158.370850, 3154.832031, 3128.137695, 3126.024170, 3119.882080, 3118.800293, 3112.137695, 3115.272461, 3120.239990, 3117.634521, 3110.083984, 3113.191162, 3106.865234, 3106.139160, 3104.727051, 3108.136719, 3102.200928, 3091.313232, 3086.746582, 3087.602539, 3082.368652, 3087.134277, 3081.679443, 3062.625488, 3046.051025, 3059.042236, 3084.889648, 3087.159668, 3081.408691, 3082.982910, 3077.339111, 3059.599854, 3053.748779, 3045.947510, 3043.497314, 3040.356445, 3039.914307, 3033.390625, 3040.936768, 3040.741455, 3040.055664, 3028.718506, 3014.827393, 3007.356445, 2999.451416, 3018.730469, 3010.055176, 3002.853516, 3006.586914, 3004.507812, 3016.617432, 3003.567139, 2979.669678, 2956.805420, 2954.939209, 2960.052979, 2969.097656, 2960.598877, 2951.389404, 2950.305664, 2948.582275, 2957.639160, 2965.738281, 2968.878662, 2978.926025, 2969.261719, 2959.451660, 2959.318848, 2956.797363, 2960.216064, 2960.466553, 2961.122314, 2966.401855, 2967.160156, 2955.267578, 2934.071533, 2938.083496, 2927.020020, 2933.566162, 2928.149658, 2934.875000, 2947.888672, 2938.209473, 2935.015625, 2918.784180, 2896.301758, 2885.999268, 2891.198242, 2900.329102, 2912.223877, 2909.698975, 2899.560059, 2900.872314, 2897.202148, 2882.148682, 2881.759766, 2877.595459, 2876.999512, 2882.008789, 2880.273438, 2876.954590, 2852.480225, 2859.835205, 2872.457520, 2873.216553, 2875.360596, 2859.402588, 2848.565430, 2841.966064, 2832.930664, 2833.967041, 2835.132080, 2834.182861, 2832.791016, 2826.254150, 2818.095215, 2813.550049, 2808.048340, 2796.335693, 2795.507812, 2784.840088, 2781.661133, 2771.555664, 2766.945312, 2760.785156, 2754.553955, 2751.051270, 2748.359131, 2747.095703, 2747.824463, 2748.955322, 2749.823730, 2754.681396, 2755.240479, 2766.260254, 2783.498291, 2790.167480, 2790.327881, 2786.945068, 2807.629150, 2802.948242, 2780.223633, 2763.153320, 2751.985107, 2739.591553, 2743.813477, 2745.824219, 2746.392090, 2734.261230, 2711.427246, 2697.594727, 2688.094727, 2681.060547, 2678.563965, 2676.426758, 2672.616943, 2670.141602, 2671.912842, 2674.090576, 2674.886719, 2687.031250, 2694.422852, 2704.653809, 2705.194824, 2707.431885, 2703.802734, 2702.704590, 2706.771729, 2709.947510, 2710.374268, 2716.076660, 2714.211914, 2709.947510, 2705.900635, 2693.977539, 2693.318604, 2693.724854, 2677.036865, 2663.982422, 2663.505371, 2663.293213, 2661.239014, 2651.581299, 2664.387695, 2668.485352, 2659.244629, 2650.893066, 2654.401855, 2645.665039, 2622.349121, 2615.928467, 2613.113281, 2622.335205, 2620.198486, 2628.669189, 2637.411133, 2636.829102, 2628.722168, 2618.313477, 2602.791992, 2607.991211, 2605.460693, 2602.505127, 2604.033936, 2598.779297, 2590.354492, 2582.988281, 2582.041748, 2578.113037, 2561.586182, 2578.240234, 2573.859375, 2560.870361, 2562.287598, 2559.698242, 2558.629639, 2563.037842, 2562.003174, 2559.747314, 2553.558105, 2542.412109, 2541.941650, 2532.588623, 2545.818359, 2538.609131, 2533.773926, 2522.790527, 2521.240234, 2526.677734, 2534.038574, 2534.315674, 2531.401611, 2525.334229, 2520.454590, 2514.272461, 2504.580078, 2490.466797, 2501.083740, 2509.501465, 2499.449463, 2501.257568, 2503.814453, 2495.574707, 2483.642090, 2479.825195, 2481.993896, 2479.338867, 2476.893066, 2479.043457, 2470.875732, 2476.181641, 2478.523193, 2482.027344, 2476.631592, 2469.090332, 2464.915283, 2453.073730, 2449.111572, 2458.299561, 2461.260010, 2450.062500, 2455.841553, 2466.629883, 2431.002441, 2422.442871, 2420.666992, 2431.450439, 2426.790283, 2413.115479, 2423.839600, 2417.269287, 2426.808838, 2401.609375, 2410.462158, 2404.278564, 2377.470703, 2390.996338, 2395.965820, 2392.956055, 2377.815430, 2394.830322, 2389.640625, 2378.451904, 2385.514893, 2403.420654, 2382.096191, 2392.702637, 2411.068115, 2376.207031, 2386.770996, 2387.080078, 2369.996094, 2372.997559, 2356.654053, 2372.019531, 2365.447510, 2367.422363, 2367.628174, 2354.479004, 2360.975098, 2348.621338, 2350.163086, 2349.685059, 2347.507812, 2336.799072, 2337.876709, 2346.638916, 2325.483398, 2326.954590, 2339.396484, 2319.987061, 2315.858643, 2324.151855, 2326.031250, 2315.992676, 2312.000000, 2318.568115, 2322.137451, 2299.980957, 2303.012939, 2317.870605, 2297.405273, 2282.087402, 2301.734619, 2295.310059, 2284.468750, 2277.786133, 2291.734619, 2290.835938, 2273.865479, 2276.751465, 2291.244385, 2271.724854, 2264.213379, 2280.357178, 2269.482178, 2255.072021, 2265.792236, 2267.423096, 2251.794189, 2262.890625, 2245.713135, 2247.020508, 2257.265381, 2249.670410, 2235.933838, 2226.108398, 2236.782959, 2226.529053, 2210.964844, 2228.283691, 2214.178955, 2216.235352, 2225.399170, 2204.786133, 2223.659424, 2206.782471, 2217.407959, 2211.240479, 2202.769775, 2199.140381, 2208.454102, 2198.734619, 2198.887451, 2189.291504, 2209.771484, 2180.977539, 2196.812988, 2181.143311, 2186.571777, 2183.200684, 2181.079102, 2183.972412, 2164.576660, 2168.396484, 2176.722412, 2153.878906, 2165.154053, 2177.580322, 2149.661621, 2157.130615, 2172.546875, 2156.648682, 2143.343506, 2149.094482, 2158.363037, 2149.923828, 2126.451416, 2145.054688, 2145.909912, 2134.679443, 2125.182617, 2145.063477, 2118.052979, 2122.547363, 2116.872070, 2110.426270, 2090.887207, 2087.033447, 2077.004883, 2070.534424, 2069.086914, 2074.855957, 2077.717773, 2088.234863, 2085.769287, 2078.004639, 2100.150879, 2105.436279, 2087.119873, 2099.774414, 2104.447510, 2108.682129, 2083.981201, 2090.560303, 2090.346680, 2077.655518, 2076.343262, 2074.630859, 2056.357666, 2075.105469, 2057.218018, 2054.425293, 2076.093506, 2052.367920, 2068.348633, 2052.741943, 2052.716797, 2050.024902, 2036.574219, 2049.227295, 2036.412720, 2048.503906, 2025.055786, 2037.170654, 2028.064209, 2022.644409, 2027.505127, 2020.419922, 2042.723877, 2013.078735, 2016.730957, 2023.204346, 2004.539795, 2015.898560, 2012.657837, 1993.505371, 2011.217407, 1996.380127, 1984.624023, 1995.896973, 1988.178955, 1984.140747, 1989.417969, 1975.577148, 1989.528564, 1976.444580, 1969.715942, 1982.681152, 1964.574097, 1969.134521, 1957.916260, 1976.642456, 1956.954102, 1957.004028, 1948.128906, 1952.422974, 1941.765015, 1935.333252, 1937.229248, 1935.185547, 1950.645386, 1932.770874, 1936.095093, 1925.579712, 1938.954590, 1921.505371, 1928.682129, 1919.575439, 1922.057983, 1908.743896, 1923.857178, 1911.191528, 1911.656128, 1900.991821, 1912.300293, 1897.100830, 1898.170532, 1905.833008, 1893.942749, 1890.502441, 1875.804565, 1884.382568, 1883.106934, 1883.549072, 1875.325317, 1880.639526, 1877.851807, 1880.340820, 1875.684937, 1874.656860, 1871.815796, 1863.395874, 1860.156738, 1854.885376, 1853.173828, 1858.678467, 1851.697144, 1849.166382, 1846.105957, 1844.309326, 1842.659180, 1845.628174, 1849.097046, 1855.793701, 1856.173706, 1846.242188, 1840.626465, 1834.270996, 1829.579346, 1828.018311, 1820.112427, 1814.949219, 1812.602539, 1816.867432, 1818.933228, 1816.341675, 1809.983154, 1800.447144, 1808.249878, 1808.697754, 1800.564209, 1801.166992, 1798.425415, 1780.773926, 1789.046021, 1797.317139, 1801.721924, 1789.765625, 1789.066406, 1787.454224, 1782.695801, 1785.656616, 1777.891235, 1773.447876, 1777.076050, 1776.183838, 1770.324951, 1766.206055, 1769.501587, 1763.008301, 1758.640259, 1753.740967, 1755.967529, 1746.908936, 1745.999146, 1739.376221, 1748.678101, 1748.426880, 1746.096313, 1740.566284, 1744.016846, 1736.652100, 1739.810913, 1742.025513, 1744.684326, 1745.950806, 1741.919922, 1732.303833, 1727.958008, 1722.328491, 1713.511963, 1713.533325, 1713.831909, 1713.204590, 1717.215576, 1725.707275, 1721.104980, 1716.185303, 1707.027588, 1705.485596, 1712.591553, 1706.577148, 1687.853638, 1687.981201, 1703.212646, 1689.519287, 1693.993286, 1690.530273, 1673.797485, 1684.872437, 1673.342041, 1680.753540, 1679.264160, 1663.246582, 1679.289062, 1660.800293, 1670.581299, 1658.962036, 1668.516846, 1659.953247, 1660.688477, 1648.842041, 1662.207031, 1647.723633, 1650.087524, 1641.994263, 1645.393311, 1642.712891, 1633.007446, 1650.527222, 1627.445068, 1636.482422, 1631.126465, 1627.835327, 1630.599731, 1613.449097, 1631.715576, 1620.109497, 1611.253906, 1625.118286, 1609.201660, 1614.976440, 1623.526367, 1600.616821, 1615.120728, 1606.291382, 1595.373901, 1605.051880, 1586.760986, 1603.716064, 1585.167480, 1600.902588, 1590.943726, 1597.599121, 1578.860596, 1592.086914, 1572.323730, 1587.334595, 1570.834595, 1581.861572, 1574.257690, 1566.027832, 1579.412720, 1564.906372, 1558.630859, 1582.640381, 1573.285400, 1553.756348, 1568.794556, 1561.710205, 1550.190430, 1570.600586, 1565.359863, 1541.303345, 1554.453369, 1547.426392, 1537.614502, 1548.699219, 1547.797852, 1533.959595, 1536.361694, 1534.859741, 1525.952393, 1545.190063, 1528.224731, 1521.119873, 1519.856934, 1517.682129, 1524.966064, 1522.444702, 1512.008911, 1511.394653, 1506.711304, 1522.249268, 1509.161011, 1502.400879, 1502.655884, 1492.638550, 1508.121582, 1489.337891, 1495.327515, 1489.607666, 1500.175659, 1486.360962, 1490.739380, 1479.145508, 1487.756836, 1474.806885, 1482.301636, 1471.592163, 1484.550781, 1460.220825, 1476.225586, 1460.590698, 1477.854736, 1452.688599, 1467.382080, 1452.090088, 1463.224243, 1464.541016, 1445.691162, 1462.853638, 1444.236206, 1441.747681, 1462.641357, 1453.140503, 1430.368408, 1438.814941, 1443.437378, 1441.155640, 1434.670044, 1426.711792, 1419.872681, 1415.835449, 1420.090454, 1421.079224, 1414.331787, 1411.143799, 1420.881104, 1424.814697, 1399.115845, 1407.817139, 1409.308350, 1394.116211, 1389.411011, 1402.574463, 1406.699951, 1383.026978, 1395.757568, 1403.281372, 1389.587158, 1390.759521, 1408.086548, 1404.818115, 1388.839233, 1399.910156, 1385.572388, 1390.198730, 1388.933594, 1382.534424, 1400.034546, 1372.217773, 1382.331909, 1375.055908, 1384.172729, 1363.220825, 1370.814087, 1345.587646, 1361.219116, 1348.516479, 1353.199219, 1328.206055, 1331.538574, 1317.769775, 1311.230347, 1301.644287, 1292.205322, 1288.922729, 1284.401245, 1284.081543, 1282.683350, 1288.511108, 1294.291504, 1291.645874, 1297.631104, 1306.333862, 1313.037598, 1312.990723, 1298.631470, 1290.776245, 1293.769043, 1298.076172, 1307.705200, 1311.318237, 1312.662231, 1309.752319, 1290.944458, 1285.414429, 1286.052246, 1279.852783, 1278.756958, 1285.073120, 1289.241455, 1297.789795, 1284.111206, 1284.292480, 1263.421875, 1253.600342, 1258.758301, 1272.456665, 1278.143066, 1277.026855, 1264.621216, 1256.042358, 1248.621582, 1245.636963, 1253.500366, 1274.987427, 1271.709961, 1261.980957, 1250.275757, 1240.558838, 1237.430298, 1243.999390, 1250.579590, 1255.930908, 1245.299805, 1234.020386, 1225.142212, 1221.047119, 1238.654419, 1222.714966, 1207.381348, 1206.129395, 1226.241211, 1201.774170, 1205.896973, 1201.129272, 1187.760620, 1215.530884, 1194.851685, 1198.098145, 1178.189209, 1202.317261, 1184.684448, 1183.822266, 1198.235474, 1179.649780, 1183.903564, 1192.738892, 1172.150635, 1172.468384, 1185.734497, 1171.282715, 1156.440796, 1153.110229, 1162.740845, 1162.235229, 1157.992798, 1140.024902, 1141.204712, 1146.810547, 1151.963989, 1149.732422, 1133.506470, 1135.100464, 1136.833984, 1142.753784, 1142.576782, 1131.229736, 1127.817139, 1127.776123, 1137.830811, 1138.334717, 1125.630127, 1122.177368, 1118.900757, 1125.445679, 1128.999390, 1111.901123, 1109.902466, 1107.172363, 1114.628174, 1115.218750, 1096.418457, 1094.879761, 1097.006348, 1101.588867, 1108.670898, 1095.233887, 1085.123413, 1083.088135, 1091.288696, 1095.461426, 1083.355103, 1086.885864, 1084.123779, 1092.417603, 1076.783691, 1077.643433, 1086.976929, 1079.270508, 1086.299072, 1077.598267, 1076.330322, 1081.947388, 1061.987061, 1081.126953, 1062.977173, 1069.987671, 1047.164062, 1069.353882, 1051.405640, 1059.812012, 1038.946045, 1056.693481, 1043.052856, 1042.240967, 1036.958862, 1035.154541, 1038.628418, 1022.399414, 1038.539429, 1018.436401, 1021.904114, 1019.155273, 1015.192993, 1024.380371, 1004.576355, 1004.083008, 1004.130676, 1003.138489, 999.540894, 1008.670410, 997.561951, 987.275818, 986.018005, 981.395996, 974.355530, 975.475403, 973.863647, 972.877197, 964.136963, 968.569946, 970.452637, 972.019043, 980.897705, 974.083618, 983.948792, 991.848389, 984.575012, 995.127625, 975.020447, 983.770081, 985.112793, 966.460632, 970.673645, 973.450867, 950.928955, 951.554260, 949.093933, 938.409912, 929.299072, 924.077942, 919.215088, 906.157837, 902.328674, 898.766479, 894.583069, 895.340393, 896.452698, 894.628052, 899.389709, 905.399719, 900.724670, 909.186646, 906.557556, 909.453552, 908.384338, 910.923279, 912.125671, 912.570679, 916.937866, 913.149170, 916.403687, 904.773926, 917.651794, 906.600403, 910.609680, 907.535950, 895.427063, 920.237610, 892.980774, 907.001709, 896.362183, 885.866882, 896.762573, 876.669800, 884.578247, 880.756042, 873.161926, 890.579529, 878.047180, 869.478027, 881.733643, 863.355713, 875.559631, 860.118042, 861.182251, 866.106079, 845.098694, 864.243103, 849.749451, 850.768311, 859.098816, 839.168762, 856.395142, 834.080750, 849.350891, 843.948364, 839.036804, 853.250366, 837.399597, 848.244263, 829.439270, 819.587280, 828.643188, 814.288086, 827.981750, 824.357178, 806.170105, 823.209106, 815.525940, 798.542664, 819.807739, 804.272888, 790.171753, 810.758057, 795.018555, 783.437073, 804.052734, 788.101624, 788.498901, 796.206909, 778.639648, 792.771057, 768.481628, 790.173889, 771.474731, 779.343994, 761.147888, 773.718689, 758.294678, 762.029663, 758.914307, 755.226440, 764.973267, 747.903320, 753.473877, 754.706055, 737.293457, 752.467346, 746.284912, 734.189392, 752.995728, 735.459167, 732.481384, 745.672607, 736.426208, 736.599548, 745.539062, 729.985291, 726.354736, 744.093445, 720.273804, 721.626526, 730.074890, 711.221619, 722.985962, 725.127075, 708.335999, 722.811218, 702.228577, 718.218323, 706.897766, 703.535889, 705.761719, 689.827393, 707.686035, 685.388916, 694.371521, 699.873779, 694.200562, 680.980896, 670.793091, 672.015869, 673.324158, 682.171082, 681.342834, 665.622253, 657.399353, 658.923889, 654.663269, 644.977844, 629.787292, 627.706604, 623.200928, 618.998840, 609.383789, 603.753357, 600.253540, 598.088745, 598.874573, 599.869324, 600.734131, 601.380554, 599.085571, 604.110535, 612.976379, 620.257141, 618.692444, 617.051636, 618.998840, 614.889160, 616.098938, 619.696594, 620.557739, 621.212891, 635.211182, 627.586365, 606.619873, 607.230957, 622.900269, 600.359009, 592.489563, 596.983887, 584.588867, 605.807861, 582.729004, 594.653137, 578.419556, 581.267334, 565.224243, 568.672363, 560.485291, 553.000000, 561.134460, 551.022827, 564.975220, 551.185120, 550.853699, 559.546875, 548.606506, 572.651428, 561.531494, 570.184875, 565.449402, 548.053528, 562.903870, 550.463379, 545.982422, 558.473206, 534.813965, 535.499146, 543.064880, 528.245789, 515.790039, 529.402039, 520.004639, 505.890228, 508.000824, 487.013947, 485.831390, 472.582031, 465.566925, 455.804565, 449.827942, 447.274567, 447.654144, 452.052612, 450.432373, 459.511078, 468.905029, 460.970306, 458.150360, 464.333191, 467.154846, 465.540131, 463.953522, 471.479523, 471.852112, 485.326569, 475.071686, 449.507629, 453.859589, 454.793671, 458.973389, 462.048553, 465.634247, 455.949066, 447.296112, 435.758423, 455.957977, 441.544800, 440.914124, 430.708527, 434.576447, 423.218994, 422.831940, 407.803314, 415.489441, 404.742706, 423.436371, 403.944885, 415.743805, 404.747406, 405.987122, 408.058014, 399.740387, 409.373444, 390.592438, 408.406860, 396.220337, 396.314880, 392.965759, 377.674408, 395.720917, 384.321594, 379.950867, 387.847504, 366.082428, 372.859253, 379.075684, 359.593231, 361.400757, 367.825958, 365.374054, 348.897705, 361.559540, 361.315887, 348.940338, 352.618561, 354.228210, 345.869568, 342.910919, 342.536194, 334.682404, 331.120605, 338.876617, 326.149109, 330.693909, 332.880066, 315.108185, 328.045258, 306.634521, 321.148376, 306.477081, 322.717834, 301.974487, 316.450714, 307.077332, 311.570709, 305.095428, 301.571228, 302.584839, 303.515167, 298.095337, 287.089447, 290.285004, 285.537262, 283.265991, 276.017273, 267.809784, 270.071991, 272.460632, 271.885620, 266.613342, 263.604034, 262.413757, 265.769379, 262.378174, 242.523666, 250.561768, 255.622818, 250.555069, 234.092209, 230.133514, 233.222076, 232.762878, 226.563812, 218.960770, 222.373230, 219.467117, 218.437485, 221.975113, 225.841797, 222.052689, 222.726151, 223.267609, 219.634033, 221.927338, 229.096146, 229.908340, 227.237564, 225.080780, 222.453369, 223.389893, 218.450836, 205.707825, -2.015127, 64.670570, 161.844238, 176.241470, 184.951538, 193.134109, 204.631866, 189.219193, 191.297852, 192.906677, 180.257904, 190.827179, 176.401535, 177.675583, 168.729370, 175.813416, 167.795731, 169.151520, 155.009598, 166.551514, 151.212082, 160.412811, 144.778564, 157.994186, 140.852783, 160.454178, 145.192078, 150.493759, 147.766846, 140.487335, 146.738693, 132.882401, 147.981049, 126.722351, 134.115982, 118.541573, 137.838974, 121.673409, 124.820946, 112.287842, 122.356667, 115.905907, 104.295166, 123.464836, 105.010803, 101.333069, 114.370987, 97.165825, 99.418030, 105.776276, 93.689240, 87.608139, 97.034882, 88.801865, 82.338432, 82.132668, 81.829094, 75.055473, 65.954262, 73.436440, 85.014267, 76.593208, 69.799713, 62.354046, 67.012405, 72.737144, 67.531647, 56.300838, 54.536110, 62.633781, 60.177620, 50.159702, 45.662914, 54.649334, 62.313072, 43.366776};

const float *DATA[] = {Data_1};

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


// selects the dataset according to a user input
const float* select_dataset(int id, const float **arr){

    return arr[id];

}


// Our handler is called from the I2C ISR, so it must complete quickly. Blocking calls 
// printing to stdio may interfere with interrupt handling.
static void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    static uint8_t chipid_byte = 0x50;
    static uint8_t comm_ready_byte = 0x10;
    static uint8_t comm_error_byte = 0x7E;
    static uint8_t comm_sr_byte = 0xB6;
    
    static uint8_t register_address = 0x00;
    static uint8_t data_received[1];

    // count variable to determine which part of the array gets sent over
    static uint32_t count = 0;

    // prompt user to input the dataset they desire
    int data_id = 0;

    std::cout << "Enter the ID of the dataset (0 for old flight data): ";
    std::cin >> data_id;

    // selects the data array based on user input
    const float* data = select_dataset(data_id, DATA);

    switch (event) {
    case I2C_SLAVE_RECEIVE: // master has written some data
        
        // writes received command to data_received
        i2c_read_raw_blocking(i2c, data_received, 1);

        break;
    case I2C_SLAVE_REQUEST: {// master is requesting data

        // send over the MAV launch command
        char mav_launch = '0';

        const uint8_t* mav_launch_int = (const uint8_t*) &mav_launch;

        i2c_write_raw_blocking(i2c, mav_launch_int, 1);

        // the data to send over
        float d = data[count];
        // printf("%.3f", d);
        // printf("\n");

        // static cast to a double
        double d_float = static_cast<double>(d) * pow(10, 6);
        // printf("%.3f", d_float);
        // printf("\n");

        // cast to an int
        const uint32_t d_int = (uint32_t) d_float;
        // printf("%d", d_int);
        // printf("\n");
        
        // initialize data array
        uint8_t d_int_arr[4] = {};

        // fill the data array
        d_int_arr[0] = d_int;
        d_int_arr[1] = d_int >> 8;
        d_int_arr[2] = d_int >> 16;
        d_int_arr[3] = d_int >> 24;

        // for (int i = 0; i < 4; i++){
        //     printf("child data[%d]: %d\n", i, d_int_arr[i]);
        // }

        // printf("\n\n\n");

        // stops the count when it reaches the end of data
        int data_length = sizeof(data) / sizeof(data[0]);
        if (count == data_length){
            d_int_arr[0] = 0;
            d_int_arr[1] = 0;
            d_int_arr[2] = 0;
            d_int_arr[3] = 0;
        }
        else{
            count++;
        }

        // send over the data array
        i2c_write_raw_blocking(i2c, d_int_arr, 4);

        // switch(data_received[0]){
        //     case 0x00:
        //         i2c_write_raw_blocking(i2c, &chipid_byte, 1);
            
        //     case 0x03:
        //         i2c_write_raw_blocking(i2c, &comm_ready_byte, 1);

        //     case 0x02:
        //         i2c_write_raw_blocking(i2c, &comm_error_byte, 1);

        //     case 0x7E:
        //         i2c_write_raw_blocking(i2c, &comm_sr_byte, 1);
            
        //     default:
        //         float d = Data_1[count];

        //         double d_float = static_cast<double>(d) * pow(10, 6);

        //         const uint32_t d_int = (uint32_t) d_float;

        //         uint8_t d_int_arr[4] = {};

        //         d_int_arr[0] = d_int;
        //         d_int_arr[1] = d_int >> 8;
        //         d_int_arr[2] = d_int >> 16;
        //         d_int_arr[3] = d_int >> 24;

        //         for (int i = 0; i < 4; i++){
        //             printf("%d", d_int_arr[i]);
        //         }

        //         printf("\n\n\n");

        //         i2c_write_raw_blocking(i2c, d_int_arr, 4);
        //         // i2c_write_raw_blocking(i2c, &d_int_arr[1], 6);
        //         // i2c_write_raw_blocking(i2c, &d_int_arr[2], 6);
        //         // i2c_write_raw_blocking(i2c, &d_int_arr[3], 6);

        //         count++;
        // }


        // if(data_received[0] == 0x0){
        //     i2c_write_raw_blocking(i2c, &response_byte, 1);
        // }
        
    
        break;
    }
    case I2C_SLAVE_FINISH: // master has signalled Stop / Restart
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

    i2c_init(I2C_PORT, I2C_BAUDRATE);
    // configure I2C0 for slave mode
    i2c_slave_init(I2C_PORT, I2C0_SLAVE_ADDR, &i2c_slave_handler);
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

    // init pins
    stdio_init_all();

    // turn on LED
    gpio_init(LED);
    gpio_set_dir(LED, GPIO_OUT);
    gpio_put(LED, 1);

    // set up child
    #if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / slave_mem_i2c example requires a board with I2C pins
        puts("Default I2C pins were not defined");
        return 0;
    #else
        puts("\nI2C child setup");

        setup_slave();
    #endif

    // infinite loop to blink the LED
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