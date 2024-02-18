#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef2_hx.h"

double **setCoef2_hx(
    char *file_name,
    double **eps,
    double **sigma,
    int y_length,
    int x_length
) {

    double **coef;

    double dt=get_dt();

    coef=init2DdoublePlane("hx coef2",y_length,x_length);

   for( int y=0;y<y_length;y++){

    for(int x=0;x<x_length;x++){

        double epsx2=2.0*eps[y][x];
        double eps_u0=eps[y][x]/u0;
        double sigmaxdt=sigma[y][x]*dt;
        double dt_dx=dt/dx;

        // coef[y][x]=2.0*dt_dx*eps_u0/(epsx2+sigmaxdt);

        coef[y][x]=2.0*dt*eps[y][x]/((epsx2+sigmaxdt)*u0*dx);

        // double test=(2.0*dt*eps[y][x]/(dx*u0))*1.0/(2.0*eps[y][x]+sigma[y][x]*dt);

        // if(test!=coef[y][x]){
        //     printf("error..\n");
        //     printf("test=%.50f\n",test);
        //     printf("coef=%.50f\n",coef[y][x]);
        //     exit(1);
        // }else{}

    }

   }

   set2DDoubleCSV((const double **)coef,file_name,y_length,x_length);


    return coef;
}
