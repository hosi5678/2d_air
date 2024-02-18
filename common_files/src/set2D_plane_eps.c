#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "../include/common_parameter.h"
#include "../include/init2DdoublePlane.h"
#include "../include/getFilePath.h"
#include "../include/set2DDoubleCSV.h"
#include "../include/set2D_plane_eps.h"

double **set2D_plane_eps(
   const char *src_file_name,
   double **n,
   int y_length,
   int x_length
){

   double **eps=init2DdoublePlane("in set2d plane eps",y_length,x_length);

   for (int y = 0 ; y < y_length ; y++ ) {
      for (int x=0 ; x<x_length ; x++ ) {
         eps[y][x]=eps0*pow(n[y][x],2.0);
      }
   }

   set2DDoubleCSV((const double **)eps,src_file_name,y_length,x_length);

   return eps;

}
