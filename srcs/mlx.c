/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/06 17:55:20 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/*
** Handle the image business.
*/

static inline void	ft_putpixel(t_env *env, int x, int y, int color)
{
	if (ft_btw(x, 0, env->win_w - 1) && ft_btw(y, 0, env->win_h - 1))
		env->imgstr[x + env->win_w * y] = color;
}

static inline int	is_env_changed(t_env *e)
{
	int res;

	res = 0;
	if (e->type == JULIA && (e->c_r != e->old_c_r || e->c_i != e->old_c_i))
	{
		e->old_c_r = e->c_r;
		e->old_c_i = e->c_i;
		res = 1;
	}
	if (e->x1 != e->old_x1 || e->x2 != e->old_x2
		|| e->y1 != e->old_y1 || e->y2 != e->old_y2
		|| e->iter_max != e->old_iter_max || e->rgb != e->old_rgb
		|| e->palette != e->old_palette)
	{
		e->old_x1 = e->x1;
		e->old_x2 = e->x2;
		e->old_y1 = e->y1;
		e->old_y2 = e->y2;
		e->old_iter_max = e->iter_max;
		e->old_rgb = e->rgb;
		e->old_palette = e->palette;
		res = 1;
	}
	return (res);
}

static inline void	process_pixel(t_env *env, int x, int y)
{
	int		iter;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	square_r;
	double	square_i;

	iter = -1;
	z_r = env->x1 + (double)x * env->step;
	z_i = env->y1 + (double)y * env->step;
	c_r = (env->type == MANDEL) ? z_r : env->c_r;
	c_i = (env->type == MANDEL) ? z_i : env->c_i;
	square_r = z_r * z_r;
	square_i = z_i * z_i;
	while (++iter < env->iter_max && (square_r + square_i) <= 4)
	{
		z_i = z_r * z_i;
		z_i += z_i + c_i;
		z_r = square_r - square_i + c_r;
		square_r = z_r * z_r;
		square_i = z_i * z_i;
	}
	if (iter != env->iter_max)
		ft_putpixel(env, x, y, palette(env, iter));
}

/*
** Render one frame when the env has changed.
*/

int					render(t_env *env)
{
	int i;
	int limit;

	i = -1;
	if (is_env_changed(env))
	{
		limit = env->win_w * env->win_h;
		ft_bzero(env->imgstr, (limit * sizeof(int)));
		while (++i < limit)
			process_pixel(env, i % env->win_w, i / env->win_w);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		printf("\nx1 = %g\tx2 = %g\tstep = %g\ty1 = %g\ty2 = %g\t\niter_max = %d", env->x1, env->x2, env->step, env->y1, env->y2, env->iter_max);
	}
	return (0);
}
