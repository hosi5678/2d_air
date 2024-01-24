#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/setSigma.h"
#include "../include/common_parameter.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/getFilePath.h"
#include "../include/set1DDoubleCSV_Column.h"

double *setSigma(int x_length){

    double *sigma;

    sigma=checkAlloc1DDouble("sigma",x_length);

    for(int x=0;x<pml_layer_half_side;x++){
        sigma[x]=cu_sigma*pow(((pml_layer_half_side-(double)x)/pml_layer_half_side),4.0);
    }

    for(int x=pml_layer_half_side;x<x_length;x++){
        sigma[x]=sigma[x_length-1-x];
    }

    char *file_path;

    file_path=getFilePath(csv_dir,"sigma",csv_extension);

    set1DDoubleCSV_Column(sigma,file_path,x_length);

    // for (int x=0 ; x<x_length ; x++) {
    //     printf("sigma[%d]=%.15f\n",x,sigma[x]);
    // }

    return sigma;

}
