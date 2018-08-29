#include "fractol.h"

void    set_mandelbrot(t_env *env)
{
        env->x1 = -2.1;
        env->x2 = 0.6;
        env->y1 = -1.2;
        env->y2 = 1.2;
        env->win_w = 1080;
        env->win_h = 960;
}