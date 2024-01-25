#include <stdio.h>
#include <stdlib.h>

#include "../include/common_parameter.h"
#include "../include/get_dt.h"
#include "../include/init2DdoublePlane.h"
#include "../include/symmetryCheck.h"
#include "../include/antisymmetryCheck.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/setEps.h"
#include "../include/setSigma.h"
#include "../include/setCoef1.h"
#include "../include/setCoef2.h"
#include "../include/setCoef3.h"
#include "../include/setCoef4.h"
#include "../include/setCoef5.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"

#include "../include/set2DEzHxHy_calc_half.h"

const double * const *set2DEzHxHy_calc_half(
    int *xylength,
    int time_length,
    double *src_J,
    int *excite_point,
    double *ez_range
){

   double *sigma,*eps;
   double **ez;

   int x_length=xylength[0];
   int y_length=xylength[1];

   printf("in calc:x_length:%d\n",x_length);
   printf("in calc:y_length:%d\n",y_length);



    return (const double * const *)ez;
}
