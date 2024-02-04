#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef1_ez.h"

const double **setCoef1_ez(
    const char *file_name,
    const double **eps,
    const double **sigma,
    int y_length,
    int x_length
) {

    double **coef;

    double dt=get_dt();

    coef=init2DdoublePlane("ez coef1",y_length,x_length);

   for( int y=0;y<y_length;y++){
    for(int x=0;x<x_length;x++){

        double sigmaxdt=sigma[y][x]*dt;
        double epsx2=2.0*eps[y][x];

        coef[y][x]=(epsx2-sigmaxdt)/(epsx2+sigmaxdt);

        // coef[y][x]=(2.0*eps[y][x]-sigma[y][x]*dt)/(2.0*eps[y][x]+sigma[y][x]*dt);
    }
   }

   set2DDoubleCSV((const double **)coef,file_name,y_length,x_length);

    return (const double **)coef;
}
