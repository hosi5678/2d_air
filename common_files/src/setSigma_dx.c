#include <math.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/getFilePath.h"
#include "../include/checkAlloc1DDouble.h"

#include "../include/setSigma_dx.h"

const double *setSigma_dx(
   int length,
   double pml_sigma
){

   double *sigma=checkAlloc1DDouble("in setSigma",length);

   for(int x=0;x<=(pml_layer_half_side+1);x++){
      sigma[x]=pml_sigma*pow((1.0-(double)x/(pml_layer_half_side+1)),4.0);
   }

    for(int x=length-(pml_layer_half_side+1);x<length;x++){
        sigma[x]=sigma[length-1-x];
    }

 return (const double *)sigma;

}
