#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <math.h>

#include "../../common_files/include/common_parameter.h"
#include "../../common_files/include/getPeak.h"
#include "../../common_files/include/get_dt.h"

#include "../include/memo_gaussian.h"

void memo_gaussian(
    const int *peak,
    double *ey_max,
    double *ey_min,
    int x_length,
    int time_length){

   int now_time_len,file_name_len;
   int fd,option,pmode;

   file_name_len=strlen("./memos/gaussian_memo_2024_01_14_Wed_17h_25min_00sec.txt");
   now_time_len=strlen("2024_01_14_Wed_17h_25min_00sec");

   char *file_name;
   file_name=(char *)calloc( file_name_len + 1 , sizeof(char) );

   char *now_time;
   now_time=(char *)calloc( now_time_len + 1 , sizeof(char) );

   time_t t=time(NULL);

   strcat(file_name,memo_dir);
   strcat(file_name,"gaussian_memo_");

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
            fprintf(fp,"gaussian pulse\n");

            fprintf(fp,"dimension=%d\n",dimension);

            fprintf(fp,"df(Nsample/(2*x_length))=%d\n",(int)round(fft_length/(2.0*x_length)));

            fprintf(fp,"x_length=%d\n",x_length);

            fprintf(fp,"time margin=%f\n",time_margin);

            fprintf(fp,"total_calc_time=%d\n",2*gaussianPeaktimePosition+x_length+fft_length);
            fprintf(fp,"fft_start_time=%d\n",2*gaussianPeaktimePosition +x_length);
            fprintf(fp,"fft_length=%d\n",fft_length);
            fprintf(fp,"fft peak number=%d\n",fft_peak_number);

            fprintf(fp,"gaussian peak point=%d\n",gaussianPeaktimePosition);
            fprintf(fp,"gaussian alpha=%f\n",gaussian_alpha);

            fprintf(fp,"dx=%.15f\n",dx);

            fprintf(fp,"light speed=%f\n",light_speed);

            double dt=get_dt();

            fprintf(fp,"dt=%.40f\n",dt);

            fprintf(fp,"ey_max(x1.1)=%.20f\n",*ey_max*1.1);
            fprintf(fp,"ey_min(x1.1)=%.20f\n",*ey_min*1.1);


            fprintf(fp,"gaussian peak\n");

            for (int i= 0 ; i< fft_peak_number;i++){
                fprintf(fp,"%d\n",peak[i]);
            }

            free(file_name);
            fclose(fp);
            // write here
        }

    }

   free(now_time);

}
