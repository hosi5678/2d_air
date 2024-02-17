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
   int y_length,
   int x_length,
   double pml_sigma
) {

    int center_y=(y_length-1)/2;
    int half_x=x_length/2-1;

    double *sigma=checkAlloc1DDouble("sigma_hy",pml_layer_half_side);

    for (int x=0;x<pml_layer_half_side;x++){
        sigma[x]=pml_sigma*pow((1.0-(double)(x+0.5)/(pml_layer_half_side)),4.0);
    }

    double **sigma_plane=init2DdoublePlane("in set sigma for hy",y_length,x_length);

    // x方向にsigmaを設定する
    for(int y=0;y<=pml_layer_half_side;y++){
        for(int x=y;x<=half_x;x++){
            sigma_plane[y][x]=sigma[y];
        }
    }

    // y方向にsigmaを設定する
    for(int x=0;x<pml_layer_half_side;x++){
        for(int y=x;y<=center_y;y++){
            sigma_plane[y][x]=sigma[x];
        }
    }

    // 右にコピーする。
    for( int y=0;y<=center_y;y++){
        for(int x=0;x<=half_x;x++){
            sigma_plane[y][x_length-1-x]=sigma_plane[y][x];
        }
    }

    // 下にコピーする。
    for( int y=0;y<center_y;y++){
        for(int x=0;x<x_length;x++){
            sigma_plane[y_length-1-y][x]=sigma_plane[y][x];
        }
    }

    set2DDoubleCSV((const double **)sigma_plane,"sigma_for_hy",y_length,x_length);

    free(sigma);

    return (const double **)sigma_plane;

}
