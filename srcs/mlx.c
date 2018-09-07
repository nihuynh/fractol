/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/07 04:26:19 by nihuynh          ###   ########.fr       */
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
	if (ft_btw(x, 0, VP_WIDTH - 1) && ft_btw(y, 0, VP_HEIGHT - 1))
		env->imgstr[x + VP_WIDTH * y] = color;
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
	c_r = (env->d.type == MANDEL) ? z_r : env->d.c_r;
	c_i = (env->d.type == MANDEL) ? z_i : env->d.c_i;
	square_r = z_r * z_r;
	square_i = z_i * z_i;
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
	int i;
	int limit;

	i = -1;
	if (env->d.changed)
	{
		env->d.changed = 0;
		limit = VP_WIDTH * VP_HEIGHT;
		ft_bzero(env->imgstr, (limit * sizeof(int)));
		while (++i < limit)
			process_pixel(env, i % VP_WIDTH, i / VP_WIDTH);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		printf("\nx1 = %g\tx2 = %g\tstep = %g\ty1 = %g\ty2 = %g\t\niter_max = %d", env->d.x1, env->d.x2, env->d.step, env->d.y1, env->d.y2, env->d.iter_max);
	}
	return (0);
}
