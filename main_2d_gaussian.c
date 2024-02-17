// copyright kenicni hoshi hosi5678@gmail.com Copyright free.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// 定数の設定
#include "./common_files/include/common_parameter.h"
#include "./common_files/include/get_dt.h"
#include "./common_files/include/checkAlloc1DDouble.h"
#include "./common_files/include/checkAlloc1DInt.h"
#include "./common_files/include/getFilePath.h"
#include "./fdtd2d_gaussian/include/setGaussianWave.h"
// #include "./common_files/include/setEtyCSV.h"
#include "./common_files/include/set1DDoubleCSV_Column.h"
#include "./common_files/include/fft.h"
#include "./common_files/include/dft.h"
#include "./common_files/include/getPeak.h"
#include "./common_files/include/frequency_analysis.h"
#include "./common_files/include/fdtd2D_calc_main.h"

#include "./fdtd2d_gaussian/include/memo_gaussian.h"

int main() {

    printf("Gaussian Pulse Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    double *exciteWave;

    int x_length,y_length;

    y_length=1+2*(refractive_layer_half_side_y+air_layer_half_side+pml_layer_half_side);
    x_length=1+2*(refractive_layer_half_side_x+air_layer_half_side+pml_layer_half_side);

    int excite_point_x,excite_point_y;
    excite_point_y=(y_length-1)/2;
    excite_point_x=(x_length-1)/2;

    double *ez_range;
    ez_range=checkAlloc1DDouble("in main ez range.",2);

    int fft_timestep_start=2*gaussianPeaktimePosition+excite_point_x;
    int fft_timestep_end=fft_timestep_start+fft_length;

    int timestep=fft_timestep_end;
    
    printf("(main) y_length=%d\n",y_length);
    printf("(main) x_length=%d\n",x_length);

    printf("(main) timestep=%d\n",timestep);
    printf("(main) gaussian peak=%d\n",gaussianPeaktimePosition);
    printf("(main) excite point_x=%d\n",excite_point_x);
    printf("(main) excite point_y=%d\n",excite_point_y);

    // gaussian wave setting
    exciteWave=setGaussianWave(timestep);

    double ez_excitePoint_max=0.0;
    double ez_excitePoint_min=0.0;

    ez_range[0]=ez_excitePoint_max;
    ez_range[1]=ez_excitePoint_min;

    const double *wave_for_fft;
    // 2 dimensional fdtd calculation
    wave_for_fft=fdtd2D_calc_main(
       x_length,
       y_length,
       timestep,
       exciteWave,
       excite_point_x,
       excite_point_y,
       ez_range
    );

    // ez_tを2のべき乗だけ後ろの方を切り取る
      double *ez_for_fft=checkAlloc1DDouble("in main ez fft.",fft_length);

      for(int time=timestep-fft_length;time<timestep;time++){
         ez_for_fft[time-timestep+fft_length]=wave_for_fft[time];
      }

      set1DDoubleCSV_Column(ez_for_fft,"./csv_files/ez_before_fft_time.csv",fft_length);

    char *file_name=getFilePath(csv_dir,"after_fft_ez_freq",csv_extension);

    const double *fft_wave=frequency_analysis(wave_for_fft,file_name,fft_length);

    file_name=getFilePath(csv_dir,"getPeak_of_fft",csv_extension);

    const int *peak=getPeak(fft_wave,file_name,fft_length);

    ez_excitePoint_max=ez_range[0];
    ez_excitePoint_min=ez_range[1];

    memo_gaussian(
        peak,
        &ez_excitePoint_max,
        &ez_excitePoint_min,
        y_length,
        x_length,
        timestep
    );

    free(exciteWave);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
