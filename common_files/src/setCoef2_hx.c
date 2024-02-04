#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef2_hx.h"

const double **setCoef2_hx(
   const double **eps,
   const double **sigma,
   int y_length,
   int x_length
) {

    double **coef;

    double dt=get_dt();

    coef=init2DdoublePlane("hx coef2",y_length,x_length);

   for( int y=0;y<y_length;y++){

    for(int x=0;x<x_length;x++){
        coef[y][x]=(2.0*dt*eps[y][x]/(dx*u0))/(2.0*eps[y][x]+sigma[y][x]*dt);
    }

   }

   set2DDoubleCSV((const double **)coef,"coef2_hx",y_length,x_length);


    return (const double **)coef;
}
