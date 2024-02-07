#include <stdio.h>

#include "../include/set_timestep_csv.h"
#include "../include/fdtd2D_calc_quad.h"

const double **fdtd2D_calc_quad(
        int timestep,

        int y_length,
        int x_length,

        int excite_point_y,
        int excite_point_x,

        const double **coef1_ez,
        const double **coef2_ez,
        const double   coef3_ez,
        const double **coef1_hx,
        const double **coef2_hx,
        const double **coef1_hy,
        const double **coef2_hy,
        double **ez,
        double **hx,
        double **hy,
        const double *src_J,
        double *ez_range
    ) {


      for ( int time = 0 ; time < timestep ; time++ ) {

         // ezの計算
         // x,yについて対称
         for( int y = 1 ; y < y_length-1 ; y++ ) {
            for ( int x = 1 ; x < x_length-1 ; x++) {
               // hx:xの並びはezと同じで、y方向の微分を行う
               double diff_hx=hx[y][x]-hx[y-1][x];

               // hy:yの並びはezと同じで,x方向の微分を行う
               double diff_hy=hy[y][x]-hy[y][x-1];

               ez[y][x]=coef1_ez[y][x]*ez[y][x]+coef2_ez[y][x]*diff_hy-coef2_ez[y][x]*diff_hx;
            }
         }

         // 励起点に電流項を追加する。
         ez[excite_point_y][excite_point_x]-=coef3_ez*src_J[time];

         // hxの計算
         // xについて対称、yについて反対称
         for(int y=0;y<y_length-1;y++){
            for(int x=0;x<x_length;x++){
               double diff_ez_dy=ez[y+1][x]-ez[y][x];
               hx[y][x]=coef1_hx[y][x]*hx[y][x]-coef2_hx[y][x]*diff_ez_dy;
            }
         }

         // hyの計算
         // yについて対称、xについて反対称
         for(int y=0;y<y_length;y++){
            for(int x=0;x<x_length-1;x++){
               double diff_ez_dx=ez[y][x+1]-ez[y][x];
               hy[y][x]=coef1_hy[y][x]*hy[y][x]+coef2_hy[y][x]*diff_ez_dx;
            }
         }

         set_timestep_csv("./ez_timestep_csvs/","ez_timestep_",ez,time,y_length,x_length);
         set_timestep_csv("./hx_timestep_csvs/","hx_timestep_",hx,time,y_length-1,x_length);
         set_timestep_csv("./hy_timestep_csvs/","hy_timestep_",hy,time,y_length,x_length-1);


      }


}
