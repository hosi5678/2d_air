#ifndef A8BEFB0B_A170_4553_9C05_2BB578F7BC3D
#define A8BEFB0B_A170_4553_9C05_2BB578F7BC3D

const double **fdtd2D_calc_quad(
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


#endif /* A8BEFB0B_A170_4553_9C05_2BB578F7BC3D */
