#ifndef A5BC9FB8_A124_4D26_BAF2_82B2A53D26A4
#define A5BC9FB8_A124_4D26_BAF2_82B2A53D26A4

#define pi 3.1415926535897932384626433832795

#define eps0 8.8541878128e-12

#define u0 1.25663706212e-6

#define light_speed 2.99792458e8
// #define light_speed 3.0e8

#define dimension 2

#define xcells 19
#define ycells 19

#define dx 20e-9 // 25e-9
#define time_margin 0.98

#define fft_length 16

#define gaussianPeaktimePosition 16

#define gaussian_alpha 0.05

#define pulseAmplitude 1.0

#define n_vacuum 1.0
#define n_test_3 3.0
#define n_air 1.000292
#define n_glass 1.55

// for test
#define refractive_layer_half_side_y 2
#define refractive_layer_half_side_x 2
// #define refractive_layer_half_side_y 2
#define air_layer_half_side 2
#define pml_layer_half_side 5

// #define reflactive_layer_half_side 60
// #define air_layer_half_side 60
// #define pml_layer_half_side 35

#define cu_sigma 64.5e6

#define fft_peak_number 15

#define csv_dir "./csv_files/"

#define timestep_dir "./ey_timestep_cvs/"

#define memo_dir "./memos/"

#define csv_extension ".csv"

#define txt_extension ".txt"

#endif /* A5BC9FB8_A124_4D26_BAF2_82B2A53D26A4 */
