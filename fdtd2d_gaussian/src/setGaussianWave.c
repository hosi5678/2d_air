#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "../../common_files/include/common_parameter.h"
#include "../../common_files/include/set1DDoubleCSV_Column.h"
#include "../../common_files/include/checkAlloc1DDouble.h"
#include "../../common_files/include/getFilePath.h"
#include "../../common_files/include/frequency_analysis.h"
#include "../../common_files/include/fft.h"
#include "../../common_files/include/dft.h"

#include "../include/setGaussianWave.h"


double *setGaussianWave(int length){

    static double *gaussian;

    double I0=pulseAmplitude;

    printf("gaussian pulse selected.\n");

    gaussian=checkAlloc1DDouble("in gaussian",length);

    // #pragma omp parallel for
    for(int i=0;i<length;i++){
		gaussian[i]=I0*exp(-gaussian_alpha*pow((i-gaussianPeaktimePosition),2.0));
	}

    char *file_path;
    file_path=getFilePath(csv_dir,"before_fft_input_gaussian_time",csv_extension);

    // #pragma omp parallel for
    set1DDoubleCSV_Column(gaussian,file_path,2*gaussianPeaktimePosition);

    // for fft
    double *fft_gaussian;
    fft_gaussian=checkAlloc1DDouble("in gaussian wave setting",2*gaussianPeaktimePosition);

    for(int time=0;time<2*gaussianPeaktimePosition;time++){
        fft_gaussian[time]=gaussian[time];
    }

    file_path=getFilePath(csv_dir,"after_fft_gaussian_freq",csv_extension);

    // fft(fft_gaussian,file_path,fft_length);

    frequency_analysis(fft_gaussian,file_path,2*gaussianPeaktimePosition);

    return gaussian;

}
