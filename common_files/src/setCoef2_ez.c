#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef2_ez.h"

double **setCoef2_ez(
    char *file_name,
    double **eps,
    double **sigma,
    int y_length,
    int x_length
) {

    double **coef;

    double dt=get_dt();

    coef=init2DdoublePlane("ez coef2",y_length,x_length);

   for( int y=0;y<y_length;y++){

    for(int x=0;x<x_length;x++){

        double epsx2=2.0*eps[y][x];
        double sigmaxdt=sigma[y][x]*dt;
        double dt_dx=dt/dx;

        coef[y][x]=2.0*dt_dx/(epsx2+sigmaxdt);

        // double test=(2.0*dt/dx)/(2.0*eps[y][x]+sigma[y][x]*dt);

        // if(test!=coef[y][x]){
        //     perror("error");
        //     printf("test=%f\n",test);
        //     exit(1);
        // }

    }

   }

   set2DDoubleCSV((const double **)coef,file_name,y_length,x_length);

    return coef;
}
