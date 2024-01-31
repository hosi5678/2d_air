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
#include "../include/setSigma_for_Hx.h"
#include "../include/setSigma_for_Hy.h"
#include "../include/setCoef1.h"
#include "../include/setCoef2.h"
#include "../include/setCoef3.h"
#include "../include/setCoef4.h"
#include "../include/setCoef5.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/put_square.h"

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

    double **eps;
    double sigma;
    const double *sigma_for_ezx,*sigma_for_ezy;    
    const double *sigma_for_hx,*sigma_for_hy;
    double **ez,**hx,**hy;

    ez=init2DdoublePlane("in ez",y_length,x_length);
    hx=init2DdoublePlane("in hx",y_length-1,x_length);
    hy=init2DdoublePlane("in hy",y_length,x_length-1);

    eps=init2DdoublePlane("in set 2D eps.",y_length,x_length);

    printf("in calc:x_length:%d\n",x_length);
    printf("in calc:y_length:%d\n",y_length);

    sigma=cu_sigma;

    sigma_for_ezx=setSigma_for_Ez(x_length,sigma);
    sigma_for_ezy=setSigma_for_Ez(y_length,sigma);
    sigma_for_hx=setSigma_for_Hx(y_length,sigma);
    sigma_for_hy=setSigma_for_Hy(x_length,sigma);




    //  ez_x=coef1(x)*ez_x+coef2(x)*(hy-hy)
    //  ez_y=coef1(y)*ez_y+coef2(y)*(hx-hx)-coef3*J
    //  ez=ez_x+ez_y
    //  hx=coef1(y)*hx+coef2(y)*(ez-ez)
    //  hy=coef1(x)*hy+coef2(x)*(ez-ez)

    //  sigma_x_for_ez,sigma_y_for_ez,sigma_x_for_hxy,sigma_y_for_hxy

    // const double *sigma_x_for_ez;
    // const double *sigma_y_for_ez;
    // const double *sigma_x_for_hxy;
    // const double *sigma_y_for_hxy;


    // n_x_for_ez=set_n_for_ez(n_ref_x_length,excite_point_x,n_ref);
    // n_y_for_ez=set_n_for_ez(n_ref_y_length,excite_point_y,n_ref);
    // n_x_for_hxy=set_n_for_hxy(n_ref_x_length,n_ref);
    // n_y_for_hxy=set_n_for_hxy(n_ref_y_length,n_ref);

    // int n_ref_x_length,n_ref_y_length;
    // double n_ref_value;

    // n_ref_value=0.0;

    // put_square(
    //     n_ref_plane,
    //     excite_point_x,
    //     excite_point_y,
    //     n_ref_x_length,
    //     n_ref_y_length,
    //     n_ref_value
    // );

    // sigma_x_for_ez=setSigma_for_Ez(x_length,sigma);
    // sigma_y_for_ez=setSigma_for_Ez(y_length,sigma);

    // sigma_x_for_hxy=setSigma_for_Hxy(x_length-1,sigma);
    // sigma_y_for_hxy=setSigma_for_Hxy(y_length-1,sigma);


    return (const double * const *)ez;
}
