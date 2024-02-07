#ifndef C1638F24_7C08_4233_92C5_F7BB9F95C121
#define C1638F24_7C08_4233_92C5_F7BB9F95C121

const double **fdtd2D_calc_full(
        int timestep,
        int y_length,
        int x_length,
        int excite_point_y,
        int excite_point_x,
        const double **coef1_ez,
        const double **coef2_ez,
        const double   coef3_ez,
        const double **coef1_hx,
        const double **coef2_hx,
        const double **coef1_hy,
        const double **coef2_hy,
        double **ez,
        double **hx,
        double **hy,
        const double *src_J,
        double *ez_range
    );

#endif /* C1638F24_7C08_4233_92C5_F7BB9F95C121 */
