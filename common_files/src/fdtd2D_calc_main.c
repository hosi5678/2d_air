#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/get_dt.h"
#include "../include/init2DdoublePlane.h"
// #include "../include/symmetryCheck.h"
// #include "../include/antisymmetryCheck.h"
// #include "../include/checkAlloc1DDouble.h"
// #include "../include/setEps.h"
#include "../include/set2DSigma_for_Ez.h"
#include "../include/set2DSigma_for_Hx.h"
#include "../include/set2DSigma_for_Hy.h"

#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"
#include "../include/set2DRefractiveIndex.h"
#include "../include/set2DDoubleCSV.h"
#include "../include/put_square.h"
#include "../include/set2D_plane_eps.h"
#include "../include/setCoef1_ez.h"
#include "../include/setCoef2_ez.h"
#include "../include/setCoef3_ez.h"
#include "../include/setCoef2_hx.h"
#include "../include/set2DDoutbleValue.h"
#include "../include/fdtd2D_calc_full.h"
#include "../include/fdtd2D_calc_quad.h"
#include "../include/fdtd2D_calc_main.h"

double *fdtd2D_calc_main(
    int x_length,
    int y_length,
    int time_length,
    double *src_J,
    int excite_point_x,
    int excite_point_y,
    double *ez_range
){

    double **eps_ez;
    double **eps_hx;
    double **eps_hy;

    double sigma;
    double refractive_index;

    double **ez,**hx,**hy;

    sigma=0.0;
    refractive_index=n_air;

    printf("in calc main:y_length:%d\n",y_length);
    printf("in calc main:x_length:%d\n",x_length);

    double **sigma_ez;
    double **sigma_hx;
    double **sigma_hy;

    sigma_ez=set2DSigma_for_Ez(y_length,x_length,sigma);
    sigma_hx=set2DSigma_for_Hx(y_length-1,x_length,sigma);
    sigma_hy=set2DSigma_for_Hy(y_length,x_length-1,sigma);

    // set refractive index 
    // writable double pointer
    
    double **n_plane_for_ez;
    double **n_plane_for_hx;
    double **n_plane_for_hy;

    n_plane_for_ez=set2DDoubleValue(y_length,x_length,n_air);
    n_plane_for_hx=set2DDoubleValue(y_length-1,x_length,n_air);
    n_plane_for_hy=set2DDoubleValue(y_length,x_length-1,n_air);

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

    eps_ez=set2D_plane_eps("ez_eps",n_plane_for_ez,y_length,x_length);
    eps_hx=set2D_plane_eps("hx_eps",n_plane_for_hx,y_length-1,x_length);
    eps_hy=set2D_plane_eps("hy_eps",n_plane_for_hy,y_length,x_length-1);

    free(n_plane_for_ez);
    free(n_plane_for_hx);
    free(n_plane_for_hy);

    double **coef1_ez;
    double **coef2_ez;
    double coef3_ez;

    coef1_ez=setCoef1_ez("coef1_ez",eps_ez,sigma_ez,y_length,x_length);
    coef2_ez=setCoef2_ez("coef2_ez",eps_ez,sigma_ez,y_length,x_length);
    coef3_ez=setCoef3_ez("coef3_ez",eps_ez,sigma_ez,excite_point_y,excite_point_x);
   
    free(sigma_ez);
    free(eps_ez);

    double **coef1_hx;
    double **coef2_hx;

    coef1_hx=setCoef1_ez("coef1_hx",eps_hx,sigma_hx,y_length-1,x_length);
    coef2_hx=setCoef2_hx("coef2_hx",eps_hx,sigma_hx,y_length-1,x_length);

    free(eps_hx);
    free(sigma_hx);

    double **coef1_hy;
    double **coef2_hy;

    coef1_hy=setCoef1_ez("coef1_hy",eps_hy,sigma_hy,y_length,x_length-1);
    coef2_hy=setCoef2_hx("coef2_hy",eps_hy,sigma_hy,y_length,x_length-1);

    free(eps_hy);
    free(sigma_hy);

    // ez,hx,hyの2次元配列を作成する。
    ez=init2DdoublePlane("(in calc main) in ez",y_length,x_length);
    hx=init2DdoublePlane("(in calc main) in hx",y_length-1,x_length);
    hy=init2DdoublePlane("(in calc main) in hy",y_length,x_length-1);

    double *vec;

    // printf("in calc main timestep=%d\n",time_length);

    vec=fdtd2D_calc_quad(
        time_length,
        y_length,
        x_length,
        excite_point_y,
        excite_point_x,
        coef1_ez,
        coef2_ez,
        coef3_ez,
        coef1_hx,
        coef2_hx,
        coef1_hy,
        coef2_hy,
        ez,
        hx,
        hy,
        src_J,
        ez_range
    );

    free(ez);
    free(hx);
    free(hy);

    free(coef1_ez);
    free(coef2_ez);
    free(coef1_hx);
    free(coef2_hx);
    free(coef1_hy);
    free(coef2_hy);

    return vec;
}
