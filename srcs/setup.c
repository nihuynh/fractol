#include "fractol.h"

void    set_mandelbrot(t_env *env)
{
        env->x1 = -2.1;
        env->x2 = 0.6;
        env->y1 = -1.2;
        env->y2 = 1.2;
        env->win_w = 1080;
        env->win_h = 960;
        env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
        env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
}