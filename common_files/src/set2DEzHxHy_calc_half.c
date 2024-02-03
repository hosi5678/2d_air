#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/get_dt.h"
#include "../include/init2DdoublePlane.h"
#include "../include/symmetryCheck.h"
#include "../include/antisymmetryCheck.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setEps.h"
#include "../include/set2DSigma_for_Ez.h"
#include "../include/set2DSigma_for_Hx.h"
#include "../include/set2DSigma_for_Hy.h"
#include "../include/setCoef1.h"
#include "../include/setCoef2.h"
#include "../include/setCoef3.h"
#include "../include/setCoef4.h"
#include "../include/setCoef5.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/set2DRefractiveIndex.h"
#include "../include/set2DDoubleCSV.h"
#include "../include/put_square.h"
#include "../include/set2D_plane_eps.h"

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

    double **eps_ez,**eps_hx,**eps_hy;
    double sigma,refractive_index;
    const double **sigma_for_ez;
    const double **sigma_for_hx,**sigma_for_hy;
    double **ez,**hx,**hy;

    sigma=cu_sigma;
    refractive_index=n_glass;

    ez=init2DdoublePlane("in ez",y_length,x_length);
    hx=init2DdoublePlane("in hx",y_length-1,x_length);
    hy=init2DdoublePlane("in hy",y_length,x_length-1);

    eps_ez=init2DdoublePlane("in set 2D eps ez.",y_length,x_length);
    eps_hx=init2DdoublePlane("in set 2D eps hx.",y_length-1,x_length);
    eps_hy=init2DdoublePlane("in set 2D eps hy.",y_length,x_length-1);

    printf("in calc:x_length:%d\n",x_length);
    printf("in calc:y_length:%d\n",y_length);

    sigma_for_ez=set2DSigma_for_Ez(
        y_length,
        x_length,
        sigma
    );

    set2DDoubleCSV(sigma_for_ez,"sigma2D_ez",y_length,x_length);

    sigma_for_hx=set2DSigma_for_Hx(
        y_length-1,
        x_length,
        sigma
    );

    set2DDoubleCSV(sigma_for_hx,"sigma2D_hx",y_length-1,x_length);

    sigma_for_hy=set2DSigma_for_Hy(
        y_length,
        x_length-1,
        sigma
    );

    set2DDoubleCSV(sigma_for_hy,"sigma2D_hy",y_length,x_length-1);

    // set refractive index 
    // writable double pointer
    double **n_plane_for_ez,**n_plane_for_hx,**n_plane_for_hy;

    n_plane_for_ez=set2DRefractiveIndex(y_length,x_length,n_air);
    n_plane_for_hx=set2DRefractiveIndex(y_length-1,x_length,n_air);
    n_plane_for_hy=set2DRefractiveIndex(y_length,x_length-1,n_air);

    put_square(
        n_plane_for_ez,
        n_plane_for_hx,
        n_plane_for_hy,
        y_length,
        x_length,
        excite_point_x,
        excite_point_y,
        refractive_index
    );

    set2DDoubleCSV(
        (const double * const *)n_plane_for_hx,
        "n_ref_plane",
        y_length-1,
        x_length);

    eps_ez=set2D_plane_eps("ez_eps",n_plane_for_ez,y_length,x_length);
    eps_hx=set2D_plane_eps("hx_eps",n_plane_for_hx,y_length-1,x_length);
    eps_hy=set2D_plane_eps("hy_eps",n_plane_for_hy,y_length,x_length-1);


    return (const double * const *)ez;
}
