#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/init2DdoublePlane.h"

double **init2DdoublePlane(const char *msg, int y_length , int x_length){

    double **plane;

    plane=(double **)calloc(y_length,sizeof(double *));

    if(NULL==plane){
        fprintf(stderr,"(in %s) can't allocate 2D plane.\n",msg);
        exit(1);
    }

    for(int y=0;y<y_length;y++){
        plane[y]=(double *)calloc(x_length,sizeof(double));

        if(NULL==plane[y]){
            fprintf(stderr,"(in %s) can't allocate 2D plane(y=%d)\n",msg,y);
        }
    }

    return plane;

}
