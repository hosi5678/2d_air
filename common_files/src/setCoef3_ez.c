
#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/get_dt.h"
#include "../include/set2DDoubleCSV.h"

#include "../include/setCoef3_ez.h"

double setCoef3_ez(
    char *file_name,
    double **eps,
    double **sigma,
    int excite_point_y,
    int excite_point_x
) {

    double coef;

    double dt=get_dt();

    int y=excite_point_y;
    int x=excite_point_x;


    double epsx2=2.0*eps[y][x];
    double sigmaxdt=sigma[y][x]*dt;

    coef=(2.0*dt)/(epsx2+sigmaxdt);

        // double test=(2.0*dt)/(2.0*eps[y][x]+sigma[y][x]*dt);

        // if(test!=coef[y][x]){
        //     printf("test=%.40f\n",test);
        //     printf("coef=%.40f\n",coef[y][x]);
        // }

    return coef;
}
