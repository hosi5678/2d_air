#include <stdio.h>

#include "../include/set2DDoubleCSV.h"
#include "../include/common_parameter.h"
#include "../include/put_square.h"

void put_square(
    double **n_plane_ez,
    double **n_plane_hx,
    double **n_plane_hy,
    int y_length,
    int x_length,
    int excite_point_x,
    int excite_point_y,
    double n_ref_value
) {

    printf("point x=%d\n",excite_point_x); // 9
    printf("point y=%d\n",excite_point_y); // 9

    printf("n_ref_value=%f\n",n_ref_value); // 9


    // for ez
    // 右下をセット
    for (int y = excite_point_y ; y <= excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x ; x <= excite_point_x+refractive_layer_half_side ; x++ ) {
            n_plane_ez[y][x]=n_ref_value;
        }
    }

    // 左下をコピー
     for (int y = excite_point_y ; y <= excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x - refractive_layer_half_side ; x < excite_point_x ; x++ ) {
            // printf("y,x=%d,%d\n",y,x);
            // printf("2*excite_point_x-x=%d\n",2*excite_point_x-x);
            n_plane_ez[y][x]=n_plane_ez[y][2*excite_point_x-x];
        }
    }
   
   // 右上,左上をコピー
   for ( int y= excite_point_y - refractive_layer_half_side ; y < excite_point_y ; y++ ){
        for(int x=excite_point_x - refractive_layer_half_side ; x <= excite_point_x + refractive_layer_half_side ; x++){
            n_plane_ez[y][x]=n_plane_ez[2*excite_point_y-y][x];
        }
   }

    set2DDoubleCSV((const double **)n_plane_ez,"n_plane_ez",y_length,x_length);

   // for hx
       // 右下をセット
    for (int y = excite_point_y ; y < excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x ; x <= excite_point_x+refractive_layer_half_side ; x++ ) {
            n_plane_hx[y][x]=n_ref_value;
        }
    }

        // 左下をコピー
     for (int y = excite_point_y ; y < excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x - refractive_layer_half_side ; x < excite_point_x ; x++ ) {
            // printf("y,x=%d,%d\n",y,x);
            // printf("2*excite_point_x-x=%d\n",2*excite_point_x-x);
            n_plane_hx[y][x]=n_plane_hx[y][2*excite_point_x-x];
        }
    }

   // 右上,左上をコピー
   for ( int y= excite_point_y - refractive_layer_half_side ; y < excite_point_y ; y++ ){
        for(int x=excite_point_x - refractive_layer_half_side ; x <= excite_point_x + refractive_layer_half_side ; x++){
            n_plane_hx[y][x]=n_plane_hx[2*excite_point_y-1-y][x];
        }
   }

    set2DDoubleCSV((const double **)n_plane_hx,"n_plane_hx",y_length-1,x_length);


    // hy
    // 右下をセット
    for (int y = excite_point_y ; y <= excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x ; x < excite_point_x+refractive_layer_half_side ; x++ ) {
            n_plane_hy[y][x]=n_ref_value;
        }
    }

    // 左下をコピー
     for (int y = excite_point_y ; y <= excite_point_y+refractive_layer_half_side ; y++ ) {
        for(int x = excite_point_x - refractive_layer_half_side ; x < excite_point_x ; x++ ) {
            n_plane_hy[y][x]=n_plane_hy[y][2*excite_point_x-1-x];
        }
    }

   // 右上,左上をコピー
   for ( int y = excite_point_y-refractive_layer_half_side ; y < excite_point_y ; y++ ){
        for(int x=excite_point_x - refractive_layer_half_side ; x < excite_point_x + refractive_layer_half_side ; x++){
            n_plane_hy[y][x]=n_plane_hy[2*excite_point_y-1-y][x];
        }
   }



    set2DDoubleCSV((const double **)n_plane_hy,"n_plane_hy",y_length,x_length-1);




}
