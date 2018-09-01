/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/01 18:05:52 by nihuynh          ###   ########.fr       */
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

static inline int	is_env_changed(t_env *env)
{
	if (env->x1 != env->old_x1 || env->x2 != env->old_x2
		|| env->y1 != env->old_y1 || env->y2 != env->old_y2
		|| env->iter_max != env->old_iter_max)
	{
		env->old_x1 = env->x1;
		env->old_x2 = env->x2;
		env->old_y1 = env->y1;
		env->old_y2 = env->y2;
		env->old_iter_max = env->iter_max;
		return (1);
	}
	return (0);
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
	z_r = 0;
	z_i = 0;
	c_r = env->x1 + (double)x * env->step_x;
	c_i = env->y1 + (double)y * env->step_y;
	square_r = z_r * z_r;
	square_i = z_i * z_i;
	while (++iter < env->iter_max && (square_r + square_i) <= 4.0)
	{
		z_i = z_r * z_i;
		z_i += z_i + c_i;
		z_r = square_r - square_i + c_r;
		square_r = z_r * z_r;
		square_i = z_i * z_i;
	}
	if (iter != env->iter_max)
		ft_putpixel(env, x, y, iter * 255 / env->iter_max << 8);
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
		mlx_clear_window(env->mlx, env->win);
		ft_bzero(env->imgstr, (limit * sizeof(int)));
		while (++i < limit)
			process_pixel(env, i % env->win_w, i / env->win_w);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		printf("\nx1 = %g\tx2 = %g\tstep_x = %g\ty1 = %g\ty2 = %g\tstep_y = %g\t\niter_max = %d", env->x1, env->x2, env->step_x, env->y1, env->y2, env->step_y, env->iter_max);
	}
	return (0);
}
