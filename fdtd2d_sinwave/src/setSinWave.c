#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

#include "../../common_files/include/common_parameter.h"
#include "../../common_files/include/checkAlloc1DDouble.h"
#include "../../common_files/include/setSinWave.h"
#include "../../common_files/include/set1DDoubleCSV_Column.h"
#include "../../common_files/include/getFilePath.h"
#include "../../common_files/include/fft.h"
#include "../../common_files/include/getPeak.h"

double *setSinWave(int angular_frequency_num,int length){

	double *wave;

	char *file_name;

   double I0=pulseAmplitude;

   printf("sin wave selected.\n");

   wave=checkAlloc1DDouble("sinwave set",length);

	for(int time=0;time<fft_length;time++){
		wave[time]=sin(2.0*pi*time*angular_frequency_num/fft_length);
	} 

	file_name=getFilePath(csv_dir,"before_fft_input_sinWave_time",csv_extension);

	set1DDoubleCSV_Column(wave,file_name,fft_length);

	const double *fft_wave;

	fft_wave=fft(wave,file_name,fft_length);

	file_name=getFilePath(csv_dir,"after_fft_sinwave_freq",csv_extension);

	set1DDoubleCSV_Column(fft_wave,file_name,fft_length);

	return wave;

}
