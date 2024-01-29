#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/setEps.h"
#include "../include/checkAlloc1DDouble.h"
#include "../include/checkAlloc1DInt.h"
#include "../include/getFilePath.h"
#include "../include/set1DIntCSV_Column.h"
#include "../include/set1DDoubleCSV_Column.h"

double *setEps(int x_length){

    double *eps;

    double n_ref=n_glass;

    printf("(in set eps) x_length=%d\n",x_length);

    double *refractive_index=checkAlloc1DDouble("in setEps ref set",x_length);

    eps=checkAlloc1DDouble("eps",x_length);

    for(int x=0;x<x_length;x++){
        eps[x]=eps0*pow(n_air,2.0);
        refractive_index[x]=n_air;
    }

    if(x_length%2==1){ // ey

        int excite_point=(x_length-1)/2;

        for(int x=excite_point;x<=excite_point+refractive_layer_half_side;x++){
            eps[x]=eps0*pow((double)n_ref,2.0);
            refractive_index[x]=n_ref;
        }

        for(int x=excite_point-refractive_layer_half_side;x<excite_point;x++){
            eps[x]=eps[x_length-1-x];
            refractive_index[x]=refractive_index[x_length-1-x];
        }

            // for(int x=0;x<x_length;x++){
            //    printf("reflactive_index[%d]=%.20f\n",x,reflactive_index[x]);
            // }

        char *file_path;
        file_path=getFilePath(csv_dir,"ref_range",csv_extension);

        int *refractive_range=checkAlloc1DInt("ref_range",2);
        refractive_range[0]=excite_point-refractive_layer_half_side;
        refractive_range[1]=excite_point+refractive_layer_half_side;

        set1DIntCSV_Column(refractive_range,file_path,2);

        file_path=getFilePath(csv_dir,"ref_value",csv_extension);

        set1DDoubleCSV_Column(refractive_index,file_path,x_length);

        free(refractive_range);

    }else{ // hz

        int excite_point=x_length/2;

        for(int x=excite_point;x<excite_point+refractive_layer_half_side-1;x++){
            eps[x]=eps0*pow((double)n_ref,2.0);
        }

        for(int x=excite_point-refractive_layer_half_side;x<excite_point;x++){
            eps[x]=eps[x_length-1-x];
        }

    }

    return eps;
}
