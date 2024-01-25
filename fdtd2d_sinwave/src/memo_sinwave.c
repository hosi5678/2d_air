#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "../../common_files/include/common_parameter.h"
#include "../../common_files/include/getPeak.h"
#include "../../common_files/include/get_dt.h"
#include "../include/memo_sinwave.h"

void memo_sinwave(int angular_frequency_num,int x_cells){

   int now_time_len,file_name_len;
   int fd,option,pmode;

   file_name_len=strlen("./memos/sin_memo_2024_01_14_Wed_17h_25min_00sec.txt");
   now_time_len=strlen("2024_01_14_Wed_17h_25min_00sec");

   char *file_name;
   file_name=(char *)calloc( file_name_len + 1 , sizeof(char) );

   char *now_time;
   now_time=(char *)calloc( now_time_len + 1 , sizeof(char) );

   time_t t=time(NULL);

   strcat(file_name,memo_dir);
   strcat(file_name,"sin_memo_");

   strftime(now_time , now_time_len + 1 ,"%Y_%m_%d_%a_%Hh_%Mmin_%Ssec", localtime(&t));

   strcat(file_name,now_time);
   strcat(file_name,txt_extension);   

   FILE *fp;

    option= O_CREAT | O_TRUNC | O_RDWR ;
    pmode= S_IRUSR | S_IWUSR | S_IROTH | S_IWOTH ;

   fd=open(file_name, option, pmode);


    if(fd == -1){
        perror("can not open the file..");
        exit(1);
    }else{

        fp=fdopen(fd,"w");

        if(NULL==fp){
            perror(file_name);
            perror(" cannot file open..\n");
            free(file_name);
            close(fd);
        }else{
            // write here
            fprintf(fp,"date:%s\n",now_time);
            fprintf(fp,"sin wave\n");
            fprintf(fp,"cells=%d\n",x_cells);
            fprintf(fp,"time margin=%f\n",time_margin);

            fprintf(fp,"timestep=%d\n",2*gaussianPeaktimePosition+x_cells+fft_length);

            fprintf(fp,"dx=%.15f\n",dx);

            double dt=get_dt();

            fprintf(fp,"dt=%.30f\n",dt);
            fprintf(fp,"angular_frequency_num=%d\n",angular_frequency_num);

            free(file_name);
            fclose(fp);
        }

    }

   free(now_time);

}
