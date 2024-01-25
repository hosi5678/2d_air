#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/get_dt.h"
#include "../include/init2DdoublePlane.h"
#include "../include/symmetryCheck.h"
#include "../include/antisymmetryCheck.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setEps.h"
#include "../include/setSigma_for_Ez.h"
#include "../include/setSigma_for_Hxy.h"
#include "../include/setCoef1.h"
#include "../include/setCoef2.h"
#include "../include/setCoef3.h"
#include "../include/setCoef4.h"
#include "../include/setCoef5.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"

#include "../include/set2DEzHxHy_calc_half.h"

const double * const *set2DEzHxHy_calc_half(
    int x_length,
    int y_length,
    int time_length,
    double *src_J,
    int excite_point_x,
    int excite_point_y,
    double *ez_range
){

    double *sigma,*eps;
    double **ez;

    printf("in calc:x_length:%d\n",x_length);
    printf("in calc:y_length:%d\n",y_length);

    //  ez_x=coef1(x)*ez_x+coef2(x)*(hy-hy)
    //  ez_y=coef1(y)*ez_y+coef2(y)*(hx-hx)
    //  ez=ez_x+ez_y
    //  hx=coef1(y)*hx+coef2(y)*(ez-ez)
    //  hy=coef1(x)*hy+coef2(x)*(ez-ez)

    //  sigma_x_for_ez,sigma_y_for_ez,sigma_x_for_hxy,sigma_y_for_hxy

    const double *sigma_x_for_ez;
    const double *sigma_y_for_ez;
    const double *sigma_x_for_hxy;
    const double *sigma_y_for_hxy;

    sigma_x_for_ez=setSigma_for_Ez(x_length,cu_sigma);
    sigma_y_for_ez=setSigma_for_Ez(y_length,cu_sigma);

    sigma_x_for_hxy=setSigma_for_Hxy(x_length-1,cu_sigma);
    sigma_y_for_hxy=setSigma_for_Hxy(y_length-1,cu_sigma);

    return (const double * const *)ez;
}
