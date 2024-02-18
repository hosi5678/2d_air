#ifndef A8BEFB0B_A170_4553_9C05_2BB578F7BC3D
#define A8BEFB0B_A170_4553_9C05_2BB578F7BC3D

    double *fdtd2D_calc_quad(
        int timestep,
        int y_length,
        int x_length,
        int excite_point_y,
        int excite_point_x,
        double **coef1_ez,
        double **coef2_ez,
        double   coef3_ez,
        double **coef1_hx,
        double **coef2_hx,
        double **coef1_hy,
        double **coef2_hy,
        double **ez,
        double **hx,
        double **hy,
        double *src_J,
        double *ez_range
    );


#endif /* A8BEFB0B_A170_4553_9C05_2BB578F7BC3D */
