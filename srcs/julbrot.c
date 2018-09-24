/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julbrot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:11:09 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/24 16:20:25 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

/*
** This set/reset the parameter of the fractal.
** It also center the origin of the complex plane.
*/

inline void		set_mandelbrot(t_fractal *data)
{
	data->type = MANDEL;
	data->x1 = M_XMIN;
	data->x2 = M_XMAX;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2;
	if (data->iter_max != ITER_MAX)
		data->new_pal = 1;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}

inline void		set_julia(t_fractal *data)
{
	data->type = JULIA;
	data->x1 = -J_X;
	data->x2 = J_X;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2;
	if (data->iter_max != ITER_MAX)
		data->new_pal = 1;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}

inline void		set_burning(t_fractal *data)
{
	data->type = BURNING;
	data->x1 = -2.7;
	data->x2 = 1.7;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2 - 0.7;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2 - 0.7;
	if (data->iter_max != ITER_MAX)
		data->new_pal = 1;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}

inline void		set_burnlia(t_fractal *data)
{
	data->type = BURNING_JULIA;
	data->x1 = -J_X;
	data->x2 = J_X;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2;
	if (data->iter_max != ITER_MAX)
		data->new_pal = 1;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}

inline void		iter_julbrot(t_env *env, t_pxl *pxl, int x, int y)
{
	t_pixel p;

	pxl->iter = -1;
	pxl->z_r = env->d.x1 + (TYPE_Z)x * env->d.step;
	pxl->z_i = env->d.y1 + (TYPE_Z)y * env->d.step;
	p.square_r = pxl->z_r * pxl->z_r;
	p.square_i = pxl->z_i * pxl->z_i;
	if (env->d.type == MANDEL)
	{
		p.d = (pxl->z_r + 1.0) * (pxl->z_r + 1.0) + p.square_i;
		p.p = sqrt((pxl->z_r - 0.25) * (pxl->z_r - 0.25) + p.square_i);
		if ((pxl->z_r - 0.25) < (p.p - (2 * p.p * p.p)) || p.d < 0.0625)
			return ;
	}
	p.c_r = (env->d.type % 2 == MANDEL) ? pxl->z_r : env->d.c_r;
	p.c_i = (env->d.type % 2 == MANDEL) ? pxl->z_i : env->d.c_i;
	while (++pxl->iter < env->d.iter_max && (p.square_r + p.square_i) <= 4)
	{
		if (env->d.type > JULIA)
		{
			pxl->z_i = Z_ABS(pxl->z_i);
			pxl->z_r = Z_ABS(pxl->z_r);
		}
		pxl->z_i = pxl->z_r * pxl->z_i;
		pxl->z_i += pxl->z_i + p.c_i;
		pxl->z_r = p.square_r - p.square_i + p.c_r;
		p.square_r = pxl->z_r * pxl->z_r;
		p.square_i = pxl->z_i * pxl->z_i;
	}
}

inline void		reiter_julbrot(t_env *env, t_pxl *pxl, int x, int y)
{
	t_pixel	p;
	TYPE_Z	vp_r;
	TYPE_Z	vp_i;

	if (pxl->iter != env->d.old_iter_max)
		return ;
	p.square_r = pxl->z_r * pxl->z_r;
	p.square_i = pxl->z_i * pxl->z_i;
	vp_r = env->d.x1 + (TYPE_Z)x * env->d.step;
	vp_i = env->d.y1 + (TYPE_Z)y * env->d.step;
	p.c_r = (env->d.type == MANDEL) ? vp_r : env->d.c_r;
	p.c_i = (env->d.type == MANDEL) ? vp_i : env->d.c_i;
	while (++pxl->iter < env->d.iter_max && (p.square_r + p.square_i) <= 4)
	{
		pxl->z_i = pxl->z_r * pxl->z_i;
		pxl->z_i += pxl->z_i + p.c_i;
		pxl->z_r = p.square_r - p.square_i + p.c_r;
		p.square_r = pxl->z_r * pxl->z_r;
		p.square_i = pxl->z_i * pxl->z_i;
	}
}
