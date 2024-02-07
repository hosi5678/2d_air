#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/set2DDoubleCSV.h"
#include "../include/init2DdoublePlane.h"

#include "../include/set2DSigma_for_Ez.h"

const double **set2DSigma_for_Ez(
   int y_length,
   int x_length,
   double pml_sigma
) {

    int center_y=(y_length-1)/2;
    int center_x=(x_length-1)/2;

    double *sigma=checkAlloc1DDouble("sigma_point",pml_layer_half_side+1);

    for (int sigma_point=0;sigma_point<=pml_layer_half_side;sigma_point++){
        sigma[sigma_point]=pml_sigma*pow((1.0-(double)sigma_point/(pml_layer_half_side+1)),4.0);
    }

    double **sigma_plane=init2DdoublePlane("in set sigma for ez",y_length,x_length);

    // x方向にsigmaを設定していく
    for(int y=0;y<=pml_layer_half_side;y++){
        for(int x=y;x<=center_x;x++){
            sigma_plane[y][x]=sigma[y];
        }
    }

    // y方向にsigmaを設定していく
    for(int x=0;x<=pml_layer_half_side;x++){
        for(int y=x;y<=center_y;y++){
            sigma_plane[y][x]=sigma[x];
        }
    }

    // 右にコピーする。
    for( int y=0;y<=center_y;y++){
        for(int x=0;x<center_x;x++){
            sigma_plane[y][x_length-1-x]=sigma_plane[y][x];
        }
    }

    // 下にコピーする。
    for( int y=0;y<center_y;y++){
        for(int x=0;x<x_length;x++){
            sigma_plane[y_length-1-y][x]=sigma_plane[y][x];
        }
    }

    // set1DDoubleCSV_Column(sigma,"./csv_files/sigma_original.csv",pml_layer_half_side+1);

    // double *sigma_x,*sigma_y;

    // sigma_x=checkAlloc1DDouble("sigma(x) ez",x_length);

    // for(int x=0;x<=(pml_layer_half_side+1);x++){
    //     sigma_x[x]=pml_sigma*pow((1.0-(double)x/(pml_layer_half_side+1)),4.0);
    // }

    // for(int x=x_length-(pml_layer_half_side+1);x<x_length;x++){
    //     sigma_x[x]=sigma_x[x_length-1-x];
    // }

    // sigma_y=checkAlloc1DDouble("sigma(y) ez",y_length);

    // for(int y=0;y<=(pml_layer_half_side+1);y++){
    //     sigma_y[y]=pml_sigma*pow((1.0-(double)y/(pml_layer_half_side+1)),4.0);
    // }

    // for(int y=y_length-(pml_layer_half_side+1);y < y_length ; y++ ) {
    //     sigma_y[y]=sigma_y[y_length-1-y];
    // }

    // char *file_path;

    // // file_path=getFilePath(csv_dir,"ez2d_sigma_x",csv_extension);
    // // set1DDoubleCSV_Column(sigma_x,file_path,x_length);


    // // 左右をコピー
    // for ( int y =pml_layer_half_side+1 ; y < y_length-pml_layer_half_side-1 ; y++ ){
    //     for ( int x =0 ; x < x_length ; x++){
    //             sigma_plane[y][x]=sigma_x[x];
    //     }
    // }

    // // 上下をコピー
    // for ( int y = 0 ; y < y_length ; y++ ){
    //     for ( int x =pml_layer_half_side+1 ; x < x_length-pml_layer_half_side-1 ; x++){
    //             sigma_plane[y][x]=sigma_y[y];
    //     }
    // }
  
    set2DDoubleCSV((const double **)sigma_plane,"sigma_for_ez",y_length,x_length);

    // free(sigma_x);
    // free(sigma_y);
    free(sigma);

    return (const double **)sigma_plane;


}
