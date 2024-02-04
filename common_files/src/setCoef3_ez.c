
#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef3_ez.h"

const double **setCoef3_ez(
    const char *file_name,
    const double **eps,
    const double **sigma,
    int x_length,
    int y_length
) {

    double **coef;

    double dt=get_dt();

    coef=init2DdoublePlane("ez coef3",y_length,x_length);

   for( int y=0;y<y_length;y++){

    for(int x=0;x<x_length;x++){

        double epsx2=2.0*eps[y][x];
        double sigmaxdt=sigma[y][x]*dt;

        coef[y][x]=(2.0*dt)/(epsx2+sigmaxdt);
        // coef[y][x]=(2.0*dt)/(2.0*eps[y][x]+sigma[y][x]*dt);
    }

   }

   set2DDoubleCSV((const double **)coef,file_name,y_length,x_length);


    return (const double **)coef;
}
