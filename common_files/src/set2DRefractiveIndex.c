#include <stdio.h>

#include "../include/init2DdoublePlane.h"
#include "../include/set2DRefractiveIndex.h"

double **set2DRefractiveIndex(
   int y_length,
   int x_length,
   double refractive_index
) {

   double **value;
   value=init2DdoublePlane("in set2Drefractive index..",y_length,x_length);

   for(int y=0;y<y_length;y++){
      for (int x=0;x<x_length;x++){
         value[y][x]=refractive_index;
      }
   }

   // for(int y=0;y<y_length;y++){
   //    for (int x=0;x<x_length;x++){
   //       printf("y:%d x:%d ref=%f\n",y,x,refractive_index);
   //    }
   // }

   return value;


}
