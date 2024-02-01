#include <stdio.h>

#include "../include/common_parameter.h"
#include "../include/put_square.h"

void put_square(
    double **n_ref_plane,
    int excite_point_x,
    int excite_point_y,
    double n_ref_value
) {

    printf("point x=%d\n",excite_point_x); // 9
    printf("point y=%d\n",excite_point_y); // 9

    printf("n_ref_value=%f\n",n_ref_value); // 9


    // 右下をセット
    for (int y = excite_point_y ; y <= excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x ; x <= excite_point_x+refractive_layer_half_side ; x++ ) {
            n_ref_plane[y][x]=n_ref_value;
        }
    }

    // 左下をコピー
     for (int y = excite_point_y ; y <= excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x - refractive_layer_half_side ; x < excite_point_x ; x++ ) {
            // printf("y,x=%d,%d\n",y,x);
            // printf("2*excite_point_x-x=%d\n",2*excite_point_x-x);
            n_ref_plane[y][x]=n_ref_plane[y][2*excite_point_x-x];
        }
    }
   
   // 右上,左上をコピー
   for ( int y= excite_point_y - refractive_layer_half_side ; y < excite_point_y ; y++ ){
        for(int x=excite_point_x - refractive_layer_half_side ; x <= excite_point_x + refractive_layer_half_side ; x++){
            n_ref_plane[y][x]=n_ref_plane[2*excite_point_y-y][x];
        }
   }

}
