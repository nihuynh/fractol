/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/09 23:44:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

/*
** Handle the image business.
*/

static inline void	ft_putpixel(t_env *env, int x, int y, int color)
{
	if (ft_btw(x, 0, VP_WIDTH - 1) && ft_btw(y, 0, VP_HEIGHT - 1))
		env->imgstr[x + VP_WIDTH * y] = color;
}

static inline int	inside_mandel(double x, double square_y)
{
	double p;
	double d;

	d = (x + 1) * (x + 1) + square_y;
	p = sqrt((x - 1 / 4) * (x - 1 / 4) + square_y);
	if (d < 16 || (x < (p - 2 * p * p + 1 / 4)))
		return (0);
	return (1);
}

static inline void	process_pixel(t_env *env, int x, int y)
{
	int		iter;
	TYPE_Z	c_r;
	TYPE_Z	c_i;
	TYPE_Z	z_r;
	TYPE_Z	z_i;
	TYPE_Z	square_r;
	TYPE_Z	square_i;

	iter = -1;
	z_r = env->d.x1 + (TYPE_Z)x * env->d.step;
	z_i = env->d.y1 + (TYPE_Z)y * env->d.step;
	square_r = z_r * z_r;
	square_i = z_i * z_i;
	if (env->d.type == MANDEL && inside_mandel(z_r, square_i))
		return ;
	c_r = (env->d.type == MANDEL) ? z_r : env->d.c_r;
	c_i = (env->d.type == MANDEL) ? z_i : env->d.c_i;
	while (++iter < env->d.iter_max && (square_r + square_i) <= 4)
	{
		z_i = z_r * z_i;
		z_i += z_i + c_i;
		z_r = square_r - square_i + c_r;
		square_r = z_r * z_r;
		square_i = z_i * z_i;
	}
	if (iter != env->d.iter_max)
		ft_putpixel(env, x, y, palette(env->d, iter));
}

/*
** Render one frame when the env has changed.
*/

int					render(t_env *env)
{
	clock_t start;
	clock_t time_frame;
	int i;
	int limit;

	i = -1;
	if (env->d.changed)
	{
		start = clock();
		env->d.changed = 0;
		limit = VP_WIDTH * VP_HEIGHT;
		ft_bzero(env->imgstr, (limit * sizeof(int)));
		while (++i < limit)
			process_pixel(env, i % VP_WIDTH, i / VP_WIDTH);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		time_frame = clock() - start;
		show_hud(env, (int) time_frame/1000);
		printf("\nx1 = %g\ty1 = %g\tc_i = %g\tstep = %g\nx2 = %g\ty2 = %g\tc_r = %g\n",
		env->d.x1, env->d.y1, env->d.c_i, env->d.step, env->d.x2, env->d.y2, env->d.c_r);
	}
	return (0);
}
