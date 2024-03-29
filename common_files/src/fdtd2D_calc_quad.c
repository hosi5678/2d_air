#include <stdio.h>

#include "../include/common_parameter.h"
#include "../include/set_timestep_csv.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/set1DDoubleTimestepCSVs.h"
#include "../include/init3DdoubleBox.h"

#include "../include/fdtd2D_calc_quad.h"

   double *fdtd2D_calc_quad(
        int timestep,

        int y_length,
        int x_length,

        int excite_point_y,
        int excite_point_x,

        double **coef1_ez,
        double **coef2_ez,
        double   coef3_ez,
        double **coef1_hx,
        double **coef2_hx,
        double **coef1_hy,
        double **coef2_hy,
        double **ez,
        double **hx,
        double **hy,
        double *src_J,
        double *ez_range // [0]:max,[1] :min
    ) {

      printf("(in quad) y_length=%d\n",y_length);
      printf("(in quad) x_length=%d\n",x_length);
      printf("(in quad) timestep=%d\n",timestep);

      int half_y=(y_length-1)/2;
      int half_x=(x_length-1)/2;

      printf("(in quad) half_y=%d\n",half_y);
      printf("(in quad) half_x=%d\n",half_x);

      double *ez_t=checkAlloc1DDouble("in quad ez",timestep);
      double ***ez_box=init3DdoubleBox("in fdtd_calc_quad",outputFrameLimit,y_length,x_length);

      for ( int time = 0 ; time < timestep ; time++ ) {

         // ezの計算
         // x,yについて対称
         // 左上を計算
         for(int y=1;y<=half_y;y++){
            for(int x=1;x<=half_x;x++){
               double diff_hx=hx[y][x]-hx[y-1][x];
               double diff_hy=hy[y][x]-hy[y][x-1];
               ez[y][x]=coef1_ez[y][x]*ez[y][x]+coef2_ez[y][x]*diff_hy-coef2_ez[y][x]*diff_hx;
            }
         }

         // for( int y = 1 ; y < y_length-1 ; y++ ) {
         //    for ( int x = 1 ; x < x_length-1 ; x++) {
         //       // hx:xの並びはezと同じで、y方向の微分を行う
         //       double diff_hx=hx[y][x]-hx[y-1][x];

         //       // hy:yの並びはezと同じで,x方向の微分を行う
         //       double diff_hy=hy[y][x]-hy[y][x-1];

         //       ez[y][x]=coef1_ez[y][x]*ez[y][x]+coef2_ez[y][x]*diff_hy-coef2_ez[y][x]*diff_hx;
         //    }
         // }

         // 励起点に電流項を付加する
         int y=excite_point_y;
         int x=excite_point_x;

         ez[y][x]-=coef3_ez*src_J[time];

         // ezの右上にcopyする
         for(int y=1;y<=half_y;y++){
            for(int x=half_x+1;x<x_length;x++){
               ez[y][x]=ez[y][x_length-1-x];
            }
         }

         // ezの下部分にcopyする
         for(int y=half_y+1;y<y_length;y++){
            for(int x=1;x<x_length;x++){
               ez[y][x]=ez[y][x]=ez[y_length-1-y][x];
            }
         }

         // hxの計算
         // xについて対称、yについて反対称
         // 左上を計算
         for(int y=0;y<half_y;y++){
            for(int x=0;x<=half_x;x++){
               double diff_ez_dy=ez[y+1][x]-ez[y][x];
               hx[y][x]=coef1_hx[y][x]*hx[y][x]-coef2_hx[y][x]*diff_ez_dy;
            }
         }

         // 右上にcopy
         for(int y=0;y<half_y;y++){
            for(int x=half_x+1;x<x_length;x++){
               hx[y][x]=hx[y][x_length-1-x];
            }
         }

         // 下にcopy (x-1.0)
          for(int y=half_y;y<y_length-1;y++){
            for(int x=1;x<x_length;x++){
               hx[y][x]=-1.0*hx[y_length-2-y][x];
            }
         }
        


         // for(int y=0;y<y_length-1;y++){
         //    for(int x=0;x<x_length;x++){
         //       double diff_ez_dy=ez[y+1][x]-ez[y][x];
         //       hx[y][x]=coef1_hx[y][x]*hx[y][x]-coef2_hx[y][x]*diff_ez_dy;
         //    }
         // }

         // hyの計算
         // yについて対称、xについて反対称
         // 左上の計算
         for(int y=0;y<=half_y;y++){
            for(int x=0;x<half_x;x++){
               double diff_ez_dx=ez[y][x+1]-ez[y][x];
               hy[y][x]=coef1_hy[y][x]*hy[y][x]+coef2_hy[y][x]*diff_ez_dx;
            }
         }

         // 左下のcopy
          for(int y=half_y+1;y<y_length;y++){
            for(int x=0;x<half_x;x++){
               hy[y][x]=hy[y_length-1-y][x];
            }
         }

         // 右側のcopy(x-1.0)
         for(int y=0;y<y_length;y++){
            for(int x=half_x;x<x_length-1;x++){
               hy[y][x]=-1.0*hy[y][x_length-2-x];
            }
         }

         // ezの波形を取得する
         ez_t[time]=ez[y][x];

         // ezの波形を3次元に代入する
         if(time<outputFrameLimit){
            for(int y=0 ; y<y_length ; y++){
               for (int x=0;x<x_length;x++){
                    ez_box[time][y][x]=ez[y][x];
               }
            }
         }

         // for(int y=0;y<y_length;y++){
         //    for(int x=0;x<x_length-1;x++){
         //       double diff_ez_dx=ez[y][x+1]-ez[y][x];
         //       hy[y][x]=coef1_hy[y][x]*hy[y][x]+coef2_hy[y][x]*diff_ez_dx;
         //    }
         // }

         // ezの横方向の波形をtimestep毎に記録する
         set1DDoubleTimestepCSVs(
            "./ez_graph_csvs/",
            "ez_graph_timestep_",
            ez[y],
            time,
            x_length
         );

         // set_timestep_csv("./ez_timestep_csvs/","ez_timestep_",ez,time,y_length,x_length);
         // set_timestep_csv("./hx_timestep_csvs/","hx_timestep_",hx,time,y_length-1,x_length);
         // set_timestep_csv("./hy_timestep_csvs/","hy_timestep_",hy,time,y_length,x_length-1);


      } // time-loop

      for(int time=2*gaussianPeaktimePosition;time<outputFrameLimit;time++){
         if(ez_t[time]>ez_range[0]) ez_range[0]=ez_t[time];
         if(ez_t[time]<ez_range[1]) ez_range[1]=ez_t[time];

      }

      for(int time=0;time<outputFrameLimit;time++) {

         double **ez_plane=ez_box[time];

         set_timestep_csv("./ez_timestep_csvs/","ez_timestep_",ez_plane,time,y_length,x_length);

      }

      printf("ez_max(*1.1)=%.20f\n",ez_range[0]*1.1);
      printf("ez_min(*1.1)=%.20f\n",ez_range[1]*1.1);

      ez_range[0]*=1.1;
      ez_range[1]*=1.1;

      set1DDoubleCSV_Column(ez_range,"./csv_files/ez_range.csv",2);

      return ez_t;

}
