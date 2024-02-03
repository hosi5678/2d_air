#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef2D_for_ez_for_J.h"

const double **setCoef2D_for_ez_for_J(
   const double **eps,
   const double **sigma,
   int y_length,
   int x_length
){

   double **coef_plane=init2DdoublePlane("int ez coef 2d J",y_length,x_length);
   double dt=get_dt();

   for ( int y = 0 ; y < y_length ; y++ ) {
      for ( int x = 0 ; x < x_length ; x++) {
            coef_plane[y][x]=(2.0*dt)/(2.0*eps[y][x]+sigma[y][x]*dt);
      }
   }

   set2DDoubleCSV((const double * const *)coef_plane,"coef2d_for_ez_J",y_length,x_length);

   return (const double **)coef_plane;

}
