#include "fractol.h"

void    set_mandelbrot(t_env *env)
{
        env->x1 = -2.15;
        env->x2 = 0.65;
        env->y1 = -1.25;
        env->y2 = 1.25;
        env->win_w = (env->x2 - env->x1) * ZOOM_VP;
        env->win_h = (env->y2 - env->y1) * ZOOM_VP;
        env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
        env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
}