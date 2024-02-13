#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../include/set1DDoubleTimestepCSVs.h"

void set1DDoubleTimestepCSVs (
   const char *dirpath,
   const char *filename,
   const double *vec,
   const int timestep,
   const int length
) {



    FILE *fp;

    int fd,option,pmode;

    option= O_CREAT | O_TRUNC | O_RDWR ;
    pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

    int file_path_length=strlen("./ez_timestep_csvs/ez_time_step_000000.csv");

   char file_number[20];
   snprintf(file_number,sizeof(file_number),"%06d",timestep);

   char *file_path = (char *)calloc(file_path_length + 1, sizeof(char) );

   strcat(file_path,dirpath);
   strcat(file_path,filename);
   strcat(file_path,file_number);
   strcat(file_path,".csv");

   // printf("time=%d,file path=%s\n",timestep,file_path);

   fd=open(file_path, option, pmode);

   if(fd == -1){
      perror("can not open the file..");
      exit(1);
   }else{

      fp=fdopen(fd,"w");

      if(NULL==fp){
         perror(file_path);
         perror(" cannot file open..\n");
         free(file_path);
         close(fd);
      }else{

            // x axisの書き込み
            // fprintf(fp,",");

            for (int x = 0; x < length; x++) {

               if(x==length-1){
                  fprintf(fp, "%d\n", x);
               }else{
                  fprintf(fp, "%d,", x);
               }
            }

            // dataの書き込み
            for (int x = 0; x < length; x++) {
               if(x==length-1){
                  fprintf(fp, "%.20f\n", vec[x]);

               }else{
                  fprintf(fp, "%.20f,", vec[x]);
               }
            }

            free(file_path);

            fclose(fp);
      }

   }

}
