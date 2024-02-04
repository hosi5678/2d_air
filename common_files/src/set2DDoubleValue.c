#include "../include/init2DdoublePlane.h"
#include "../include/set2DDoutbleValue.h"

double **set2DDoubleValue(int y_length,int x_length,double value){

   double **plane=init2DdoublePlane("in set2d double",y_length,x_length);

   for ( int y = 0 ; y < y_length ; y++ ) {
      for ( int x = 0 ; x < x_length ; x++) {
         plane[y][x]=value;
      }
   }

   return plane;

}
