#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/init2DdoublePlane.h"
#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/set2DSigma_for_Hy.h"

const double **set2DSigma_for_Hy(
//    const char *file_name,
   int y_length,
   int x_length,
   double sigma
) {

    printf("in hy sigma y_length=%d\n",y_length);
    printf("in hy sigma x_length=%d\n",x_length);

    double *sigma_x,*sigma_y;
    char *file_path;

    sigma_x=checkAlloc1DDouble("sigma_x_hy",x_length);

    for(int x=0;x<pml_layer_half_side;x++){
        sigma_x[x]=sigma*pow(1.0-((double)(x+0.5)/pml_layer_half_side),4.0);
        sigma_x[x_length-1-x]=sigma_x[x];
    }

    file_path=getFilePath(csv_dir,"sigma_x_hy",csv_extension);

    set1DDoubleCSV_Column(sigma_x,file_path,x_length);

    sigma_y=checkAlloc1DDouble("sigma_y_hy",y_length);

    for(int y=0;y<=pml_layer_half_side+1;y++){
        sigma_y[y]=sigma*pow(1.0-((double)(y)/(pml_layer_half_side+1)),4.0);
        sigma_y[y_length-1-y]=sigma_y[y];
    }

    file_path=getFilePath(csv_dir,"sigma_y_hy",csv_extension);

    set1DDoubleCSV_Column(sigma_y,file_path,y_length);

    double **sigma_plane;

    sigma_plane=init2DdoublePlane("hy 2d sigma.",y_length,x_length);

    //  左右のコピー
    for ( int y = pml_layer_half_side + 1 ; y < y_length-1-pml_layer_half_side ; y++ ) {
        for( int x = 0 ; x < x_length ; x++ ) {
            sigma_plane[y][x]=sigma_x[x];
        }
    }

    // hyはx方向に微分されるので,y方向のsetは不要
    // 上下のコピー
    //  for ( int y = 0 ; y < y_length ; y++ ) {
    //     for( int x = pml_layer_half_side ; x <= x_length-pml_layer_half_side ; x++ ) {
    //         sigma_plane[y][x]=sigma_y[y];
    //     }
    // }

    set2DDoubleCSV((const double **)sigma_plane,"sigma2DPlane_hy",y_length,x_length);

    free(sigma_x);
    free(sigma_y);

    return (const double **)sigma_plane;

}
