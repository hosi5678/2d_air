#include <stdio.h>
#include <stdlib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"

#include "../include/setSigma_for_Ez.h"

const double *setSigma_for_Ez(int x_length,double pml_sigma){

    double *sigma;

    sigma=checkAlloc1DDouble("sigma",x_length);

    for(int x=0;x<pml_layer_half_side;x++){
        sigma[x]=pml_sigma*pow((1.0-(double)x/pml_layer_half_side),4.0);
    }

    for(int x=x_length-pml_layer_half_side;x<x_length;x++){
        sigma[x]=sigma[x_length-1-x];
    }

    char *file_path;

    file_path=getFilePath(csv_dir,"sigma",csv_extension);

    set1DDoubleCSV_Column(sigma,file_path,x_length);

   //  for (int x=0 ; x<x_length ; x++) {
   //      printf("sigma[%d]=%.15f\n",x,sigma[x]);
   //  }

    return sigma;


}
