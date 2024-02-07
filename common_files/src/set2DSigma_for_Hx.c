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

#include "../include/set2DSigma_for_Hx.h"

const double **set2DSigma_for_Hx(
   int y_length,
   int x_length,
   double pml_sigma
) {

    int half_y=y_length/2-1;
    int center_x=(x_length-1)/2;

    double *sigma=checkAlloc1DDouble("sigma_point",pml_layer_half_side);

    for (int y=0;y<pml_layer_half_side;y++){
        sigma[y]=pml_sigma*pow((1.0-(double)(y+0.5)/(pml_layer_half_side)),4.0);
    }

    double **sigma_plane=init2DdoublePlane("in set sigma for hx",y_length,x_length);

    // x方向にsigmaを設定していく
    for(int y=0;y<pml_layer_half_side;y++){
        for(int x=y;x<=center_x;x++){
            sigma_plane[y][x]=sigma[y];
        }
    }

    // y方向にsigmaを設定していく
    for(int x=0;x<=pml_layer_half_side;x++){
        for(int y=x;y<=half_y;y++){
            sigma_plane[y][x]=sigma[x];
        }
    }

    // 右にコピーする。
    for( int y=0;y<=half_y;y++){
        for(int x=0;x<center_x;x++){
            sigma_plane[y][x_length-1-x]=sigma_plane[y][x];
        }
    }

    // 下にコピーする。
    for( int y=0;y<=half_y;y++){
        for(int x=0;x<x_length;x++){
            sigma_plane[y_length-1-y][x]=sigma_plane[y][x];
        }
    }

    // set1DDoubleCSV_Column(sigma,"./csv_files/sigma_original.csv",pml_layer_half_side+1);


//     printf("in hx sigma y_length=%d\n",y_length);
//     printf("in hx sigma x_length=%d\n",x_length);

//     double *sigma_x,*sigma_y;
//     char *file_path;

//     sigma_x=checkAlloc1DDouble("sigma_x_hx",x_length);

//     for(int x=0;x<=(pml_layer_half_side+1);x++){
//         sigma_x[x]=sigma*pow((1.0-(double)x/(pml_layer_half_side+1)),4.0);
//     }

//     for(int x=x_length-(pml_layer_half_side+1);x<x_length;x++){
//         sigma_x[x]=sigma_x[x_length-1-x];
//     }

//     // file_path=getFilePath(csv_dir,"sigma_hx_x",csv_extension);
//     // set1DDoubleCSV_Column(sigma_x,file_path,x_length);

//     sigma_y=checkAlloc1DDouble("sigma_y_hx",y_length);

//     for(int y=0;y<pml_layer_half_side;y++){
//         sigma_y[y]=sigma*pow(1.0-((double)(y+0.5)/(pml_layer_half_side)),4.0);
//     }

//     for(int y=0;y<pml_layer_half_side;y++){
//         sigma_y[y_length-1-y]=sigma_y[y];
//     }

//     // file_path=getFilePath(csv_dir,"sigma_hx_y",csv_extension);
//     // set1DDoubleCSV_Column(sigma_y,file_path,y_length);

//     double **sigma_plane;

//     sigma_plane=init2DdoublePlane("hx 2d sigma.",y_length,x_length);

//     // hxはy方向に微分される。x方向は不要
//     // 左右をコピー
//     // for ( int y =pml_layer_half_side ; y < y_length-pml_layer_half_side ; y++ ){
//     //     for ( int x =0 ; x < x_length ; x++){
//     //             sigma_plane[y][x]=sigma_x[x];
//     //     }
//     // }

//     // 上下のコピー
//      for ( int y = 0 ; y < y_length ; y++ ) {
//         for( int x = pml_layer_half_side+1 ; x < x_length-pml_layer_half_side ; x++ ) {
//             sigma_plane[y][x]=sigma_y[y];
//         }
//     }

//     set2DDoubleCSV((const double **)sigma_plane,"sigma_2DPlane_hx",y_length,x_length);
   
//    free(sigma_x);
//    free(sigma_y);

    set2DDoubleCSV((const double **)sigma_plane,"sigma_for_hx",y_length,x_length);

    free(sigma);

    return (const double **)sigma_plane;

}
