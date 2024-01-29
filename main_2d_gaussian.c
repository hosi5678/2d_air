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
#include "./common_files/include/setGaussianWave.h"
#include "./common_files/include/set1DEyHz.h"
#include "./common_files/include/set2DEzHxHy_calc_half.h"
#include "./common_files/include/setEtyCSV.h"
#include "./common_files/include/set_ey_timestep_csv.h"
#include "./common_files/include/set1DDoubleCSV_Column.h"
#include "./common_files/include/fft.h"
#include "./common_files/include/dft.h"
#include "./common_files/include/getPeak.h"
#include "./common_files/include/frequency_analysis.h"

#include "./fdtd2d_gaussian/include/memo_gaussian.h"

int main(void) {

    printf("Gaussian Pulse Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    const double * const *ety_const_2d_plane;
    double *exciteWave;

    char *file_name;

    int x_length,y_length;
    x_length=1+2*(refractive_layer_half_side+air_layer_half_side+pml_layer_half_side);
    y_length=1+2*(refractive_layer_half_side+air_layer_half_side+pml_layer_half_side);

    int excite_point_x,excite_point_y;
    excite_point_x=(x_length-1)/2;
    excite_point_y=(y_length-1)/2;

    double *ez_range;
    ez_range=checkAlloc1DDouble("in main ez range.",2);

    int fft_timestep_start=2*gaussianPeaktimePosition+excite_point_x;
    int fft_timestep_end=fft_timestep_start+fft_length;

    int calculation_timestep=fft_timestep_end;

    printf("(main) x_length=%d\n",x_length);
    printf("(main) y_length=%d\n",y_length);


    printf("(main) calc timestep=%d\n",calculation_timestep);
    printf("(main) gaussian peak=%d\n",gaussianPeaktimePosition);
    printf("(main) excite point_x=%d\n",excite_point_x);
    printf("(main) excite point_y=%d\n",excite_point_y);

    // gaussian wave setting
    exciteWave=setGaussianWave(calculation_timestep);

    double ez_excitePoint_max=0.0;
    double ez_excitePoint_min=0.0;

    ez_range[0]=ez_excitePoint_max;
    ez_range[1]=ez_excitePoint_min;

    // 1 dimensional fdtd calculation
    ety_const_2d_plane=set2DEzHxHy_calc_half(
       x_length,
       y_length,
       calculation_timestep,
       exciteWave,
       excite_point_x,
       excite_point_y,
       ez_range
    );

    // file_name=getFilePath(csv_dir,"eyt_plane_2d",csv_extension);

    // setEtyCSV(ety_const_2d_plane,file_name,fft_timestep_end,x_cells);

    // set_ey_timestep_csv(ety_const_2d_plane,"./ey_timestep_csvs/",calculation_timestep,x_cells);

    // // fft calculation , array allocation
    // double *fft_array=checkAlloc1DDouble("in main fft alloc",fft_length);

    // // data copy
    // for(int time=fft_timestep_start;time<fft_timestep_start+fft_length;time++){

    //     for(int x=0;x<x_cells;x++){
    //         if(x==excite_point){
    //             fft_array[time-fft_timestep_start]=ety_const_2d_plane[time][x];
    //         }

    //     }
    // }

    // // fft_processing
    // // file name setting
    // file_name=getFilePath(csv_dir,"before_fft_eyt_time",csv_extension);

    // // set csv value
    // set1DDoubleCSV_Column(fft_array,file_name,fft_length);

    // file_name=getFilePath(csv_dir,"after_fft_eyt_freq",csv_extension);

    // const double *fft_wave=frequency_analysis(fft_array,file_name,fft_length);

    // file_name=getFilePath(csv_dir,"getPeak_of_fft",csv_extension);

    // const int *peak;

    // peak=getPeak(fft_wave,file_name,fft_length);

    // printf("(main) gaussian fft peak df=%d\n",(int)round(fft_length/(2.0*x_cells)));

    // memo_gaussian(peak,&ey_max,&ey_min,x_cells,calculation_timestep);

    free(exciteWave);
    // free(fft_array);
    // free(file_name);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
