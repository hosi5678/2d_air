#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/getFilePath.h"
#include "../include/set2DDoubleCSV.h"
#include "../include/set2D_eps_for_ez.h"

double **set2D_eps_for_ez(
   const char *src_file_name,
   // const double * const *n,
   double **n,
   int y_length,
   int x_length
){

   for (int y = 0 ; y < y_length ; y++ ) {
      for (int x=0 ; x<x_length ; x++ ) {
         n[y][x]=eps0*pow(n[y][x],2.0);
      }
   }

   set2DDoubleCSV((const double * const *)n,src_file_name,y_length,x_length);

   return n;

}
