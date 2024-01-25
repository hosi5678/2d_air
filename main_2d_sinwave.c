// copyright kenicni hoshi hosi5678@gmail.com Copyright free.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// 定数の設定
#include "./common_files/include/common_parameter.h"
#include "./common_files/include/init2DdoublePlane.h"
#include "./common_files/include/getFilePath.h"
#include "./common_files/include/setSinWave.h"
#include "./common_files/include/set1DEyHz.h"
#include "./common_files/include/set1DEyHz_half_calc.h"
#include "./common_files/include/setEtyCSV.h"
#include "./common_files/include/set_ey_timestep_csv.h"

#include "./fdtd1d_sinwave/include/memo_sinwave.h"

int main(int argc,char **argv) {

    printf("Sin Wave Excitation.\n");

    time_t start_clock, end_clock;

    start_clock = clock();

    printf("argc=%d,argv=%s\n",argc,argv[1]);

    const int angular_frequency_num=atoi(argv[1]);
    
    double const * const *ety_const_2d_plane;
    double *exciteWave;

    char *file_name;

    int x_cells=1+2*(air_layer_half_side+reflactive_layer_half_side+pml_layer_half_side);

    int excite_point=air_layer_half_side+reflactive_layer_half_side+pml_layer_half_side; //(cells-1)/2;

    int calculation_timestep=fft_length;

    printf("(main) cells=%d\n",x_cells);
    printf("(main) calculation timestep=%d\n",calculation_timestep);
    printf("angular frequency number=%d\n",angular_frequency_num);

    // wave initialize
    exciteWave=setSinWave(angular_frequency_num,calculation_timestep);

    double ey_max=0.0;
    double ey_min=0.0;

    // 1 dimensional fdtd calculation
    ety_const_2d_plane=set1DEyHz_half_calc(
        x_cells,
        calculation_timestep,
        exciteWave,
        excite_point,
        &ey_max,
        &ey_min
    );

    file_name=getFilePath(csv_dir,"eyt_plane_2d",csv_extension);

    setEtyCSV(ety_const_2d_plane,file_name,fft_length,x_cells);

    set_ey_timestep_csv(ety_const_2d_plane,"./ey_timestep_csvs/",fft_length,x_cells);

    memo_sinwave(angular_frequency_num,x_cells);

    free(exciteWave);

    end_clock = clock();

    printf("(main) processing time=%f(sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);

    return 0;
}
