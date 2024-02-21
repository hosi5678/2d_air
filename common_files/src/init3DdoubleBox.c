#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/init2DdoublePlane.h"
#include "../include/init3DdoubleBox.h"

double ***init3DdoubleBox(
   const char *msg ,
   int z_length , 
   int y_length , 
   int x_length
) {

   double ***box = (double ***)calloc(z_length,sizeof(double **));

   if(NULL==box){
      fprintf(stderr,"(in %s) can't allocate 3D plane.\n",msg);
      exit(1);
   }

   for(int z=0 ; z <z_length;z++){
      box[z]=init2DdoublePlane("3D box",y_length,x_length);
   }

   return box;

}
