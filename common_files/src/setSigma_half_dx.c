#include <math.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/getFilePath.h"
#include "../include/checkAlloc1DDouble.h"

#include "../include/setSigma_half_dx.h"

const double *setSigma_half_dx(
   int length,
   double pml_sigma
){

   double *sigma=checkAlloc1DDouble("in setSigma",length);

    for(int y=0;y<pml_layer_half_side;y++){
        sigma[y]=pml_sigma*pow(1.0-((double)(y+0.5)/(pml_layer_half_side)),4.0);
    }

    for(int y=0;y<pml_layer_half_side;y++){
        sigma[length-1-y]=sigma[y];
    }

   return (const double *)sigma;

}
