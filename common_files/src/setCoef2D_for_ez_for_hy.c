#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef2D_for_ez_for_hy.h"

const double **setCoef2D_for_ez_for_hy(
   const double **eps,
   const double **sigma,
   int y_length,
   int x_length){

   double **coef_plane=init2DdoublePlane("in ez coef 2d hy",y_length,x_length);
   double dt=get_dt();

   for ( int y = 0 ; y < y_length ; y++ ) {
      for ( int x = 0 ; x < x_length ; x++) {
            coef_plane[y][x]=(2.0*dt)/((2.0*eps[y][x]+sigma[y][x]*dt)*dx);
      }
   }

   set2DDoubleCSV((const double * const *)coef_plane,"coef2d_for_ez_hy",y_length,x_length);

   return (const double **)coef_plane;
}
