#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/set2DDoubleCSV.h"

void set2DDoubleCSV(
   const double **vec,
   const char *src_file_name,
   int y_length,
   int x_length
){

    FILE *fp;

    int fd,option,pmode;

    option= O_CREAT | O_TRUNC | O_RDWR ;
    pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

    int file_name_length;

    file_name_length = strlen(src_file_name);

    char *file_name;
    file_name = (char *)calloc(file_name_length + 1, sizeof(char) );

    strcpy(file_name, src_file_name);

    fd=open(file_name, option, pmode);

    if(fd == -1){
        perror("can not open the file..");
        exit(1);
    }else{

        fp=fdopen(fd,"w");

        if(NULL==fp){
            perror(file_name);
            perror(" cannot open the file ..\n");
            free(file_name);
            close(fd);
        }else{
            // write here

         // x axisの書き込み
         // tabの書き込み
         fprintf(fp,"\t");

         for(int x=0;x<x_length;x++){
            if(x==x_length-1){
               fprintf(fp, "%d\n", x);
            }else{
               fprintf(fp, "%d,", x);
            }
         }

         // dataの書き込み
         for (int y = 0; y < y_length; y++) {

               // y座標の書き込み
            fprintf( fp , "%d," , y );
 
            for (int x= 0 ; x < x_length ; x++){
               if(x==x_length-1){
                 fprintf(fp, "%.20f\n", vec[y][x]);
               }else{
                 fprintf(fp, "%.20f,", vec[y][x]);
               }
            } // x-loop

         } // y-loop

            free(file_name);

            fclose(fp);
            // write here
        }

    }




}
