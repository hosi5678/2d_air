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

#include "../include/setSigma_for_Hx.h"

const double *setSigma_for_Hx(int y_length, double pml_sigma){

    double *sigma;

    sigma=checkAlloc1DDouble("sigma",y_length);

    for(int y=0;y<pml_layer_half_side;y++){
        sigma[y]=pml_sigma*pow(1.0-((double)(y+0.5)/pml_layer_half_side),4.0);
    }

    for(int y=0;y<pml_layer_half_side;y++){
        sigma[y_length-1-y]=sigma[y];
    }

    char *file_path;

    file_path=getFilePath(csv_dir,"sigma_hx",csv_extension);

    set1DDoubleCSV_Column(sigma,file_path,y_length);

    // for (int y=0 ; y<y_length ; y++) {
    //     printf("sigma_hx[%d]=%.15f\n",y,sigma[y]);
    // }

    return (const double *)sigma;

}
