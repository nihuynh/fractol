#include "fractol.h"
#include <math.h>

/*
** This color the pixel for Julia and Mandelbrot fractals.
** Check if inside mandel to avoid compute black pixel.
** Check for the cardioid and the first circle.
*/

static inline void	iter_mj(t_slice *env, t_pxl *pxl)
{
	t_pixel p;

	pxl.iter = -1;
	pxl.z_r = env->d.x1 + (TYPE_Z)x * env->d.step;
	pxl.z_i = env->d.y1 + (TYPE_Z)y * env->d.step;
	p.square_r = pxl.z_r * pxl.z_r;
	p.square_i = pxl.z_i * pxl.z_i;
	if (env->d.type == MANDEL)
	{
		p.d = (pxl.z_r + 1.0) * (pxl.z_r + 1.0) + p.square_i;
		p.p = sqrt((pxl.z_r - 0.25) * (pxl.z_r - 0.25) + p.square_i);
		if ((pxl.z_r - 0.25) < (p.p - (2 * p.p * p.p)) || p.d < 0.0625)
			return ;
	}
	p.c_r = (env->d.type == MANDEL) ? pxl.z_r : env->d.c_r;
	p.c_i = (env->d.type == MANDEL) ? pxl.z_i : env->d.c_i;
	while (++pxl.iter < env->d.iter_max && (p.square_r + p.square_i) <= 4)
	{
		pxl.z_i = pxl.z_r * pxl.z_i;
		pxl.z_i += pxl.z_i + p.c_i;
		pxl.z_r = p.square_r - p.square_i + p.c_r;
		p.square_r = pxl.z_r * pxl.z_r;
		p.square_i = pxl.z_i * pxl.z_i;
	}
}
