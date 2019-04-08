/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julbrot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:11:09 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 22:40:02 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

inline static int	inside_mandel(TYPE_Z z_r, TYPE_Z square_i)
{
	TYPE_Z p;
	TYPE_Z d;

	d = (z_r + 1.0) * (z_r + 1.0) + square_i;
	p = sqrt((z_r - 0.25) * (z_r - 0.25) + square_i);
	if ((z_r - 0.25) < (p - (2 * p * p)) || d < 0.0625)
		return (1);
	return (0);
}

inline void			iter_julbrot(t_env *env, t_pxl *pxl, int x, int y)
{
	t_pixel p;

	pxl->iter = -1;
	p.z_r = env->d.x1 + (TYPE_Z)x * env->d.step;
	p.z_i = env->d.y1 + (TYPE_Z)y * env->d.step;
	p.square_r = p.z_r * p.z_r;
	p.square_i = p.z_i * p.z_i;
	if (env->d.type == MANDEL && inside_mandel(p.z_r, p.square_i))
		return ;
	p.c_r = (env->d.type % 2 == MANDEL) ? p.z_r : env->d.c_r;
	p.c_i = (env->d.type % 2 == MANDEL) ? p.z_i : env->d.c_i;
	while (++pxl->iter < env->d.iter_max && (p.square_r + p.square_i) <= 4)
	{
		if (env->d.type > JULIA)
			p.z_r = -Z_ABS(p.z_r);
		if (env->d.type == BURNING || env->d.type == BURNING_JULIA)
		{
			p.z_i = Z_ABS(p.z_i);
			p.z_r = -p.z_r;
		}
		p.z_i = p.z_r * p.z_i;
		p.z_i += p.z_i + p.c_i;
		p.z_r = p.square_r - p.square_i + p.c_r;
		p.square_r = p.z_r * p.z_r;
		p.square_i = p.z_i * p.z_i;
	}
}

inline void			reiter_julbrot(t_env *env, t_pxl *pxl, int x, int y)
{
	if (pxl->iter < 0 || pxl->iter > env->d.iter_max)
		return ;
	if (env->imgstr[x + y * VP_WIDTH] == 0)
		iter_julbrot(env, pxl, x, y);
}
