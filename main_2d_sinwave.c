// copyright kenicni hoshi hosi5678@gmail.com Copyright free.
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
#include "./fdtd2d_sinwave/include/setSinWave.h"
#include "./common_files/include/set1DDoubleCSV_Column.h"
#include "./common_files/include/fft.h"
#include "./common_files/include/dft.h"
#include "./common_files/include/getPeak.h"
#include "./common_files/include/fdtd2D_calc_main.h"

#include "./fdtd2d_sinwave/include/memo_sinwave.h"

int main(int argc,char **argv) {

    printf("Sin Wave Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    printf("argc=%d,argv=%s\n",argc,argv[1]);

    int angular_frequency_num=atoi(argv[1]);
    
    double *exciteWave;

    int x_length;
    int y_length;

    y_length=1+2*(refractive_layer_half_side_y+air_layer_half_side+pml_layer_half_side);
    x_length=1+2*(refractive_layer_half_side_x+air_layer_half_side+pml_layer_half_side);

    int excite_point_x;
    int excite_point_y;

    excite_point_y=(y_length-1)/2;
    excite_point_x=(x_length-1)/2;

    double *ez_range;
    ez_range=checkAlloc1DDouble("in main ez range.",2);

    int fft_timestep_start=2*gaussianPeaktimePosition+excite_point_x;
    int fft_timestep_end=fft_timestep_start+fft_length;

    int calculation_timestep=fft_timestep_end;

    // int calculation_timestep=1200;

    // calculation_timestep=1800;
    
    printf("(main) y_length=%d\n",y_length);
    printf("(main) x_length=%d\n",x_length);

    printf("(main) calc timestep=%d\n",calculation_timestep);
    printf("(main) gaussian peak=%d\n",gaussianPeaktimePosition);
    printf("(main) excite point_x=%d\n",excite_point_x);
    printf("(main) excite point_y=%d\n",excite_point_y);

    // gaussian wave setting
    exciteWave=setSinWave(angular_frequency_num,fft_length);

    double ez_excitePoint_max=0.0;
    double ez_excitePoint_min=0.0;

    ez_range[0]=ez_excitePoint_max;
    ez_range[1]=ez_excitePoint_min;

    double *wave_for_fft;

    // 2 dimensional fdtd calculation
    wave_for_fft=fdtd2D_calc_main(
       x_length,
       y_length,
       calculation_timestep,
       exciteWave,
       excite_point_x,
       excite_point_y,
       ez_range
    );

    memo_sinwave(angular_frequency_num,y_length,x_length);

    free(exciteWave);
    free(wave_for_fft);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
