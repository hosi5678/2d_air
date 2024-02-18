#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/checkAlloc1DDouble.h"

double *checkAlloc1DDouble(char *str_msg,int length){

     double *vec = (double *)calloc(length, sizeof(double));

    if (NULL == vec) {
        fprintf(stderr, "%s\n", str_msg);
        perror("calloc error. exit...\n");
        exit(1);
    }
    
    return vec;

}
