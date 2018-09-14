/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/14 18:18:02 by nihuynh          ###   ########.fr       */
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

/*
** This color the pixel for Julia and Mandelbrot fractals.
** Check if inside mandel to avoid compute black pixel.
** Check for the cardioid and the first circle.
*/

static inline void	process_pixel(t_env *env, int x, int y)
{
	t_pixel p;

	p.iter = -1;
	p.z_r = env->d.x1 + (TYPE_Z)x * env->d.step;
	p.z_i = env->d.y1 + (TYPE_Z)y * env->d.step;
	p.square_r = p.z_r * p.z_r;
	p.square_i = p.z_i * p.z_i;
	if (env->d.type == MANDEL)
	{
		p.d = (p.z_r + 1.0) * (p.z_r + 1.0) + p.square_i;
		p.p = sqrt((p.z_r - 0.25) * (p.z_r - 0.25) + p.square_i);
		if ((p.z_r - 0.25) < (p.p - (2 * p.p * p.p)) || p.d < 0.0625)
			return ;
	}
	p.c_r = (env->d.type == MANDEL) ? p.z_r : env->d.c_r;
	p.c_i = (env->d.type == MANDEL) ? p.z_i : env->d.c_i;
	while (++p.iter < env->d.iter_max && (p.square_r + p.square_i) <= 4)
	{
		p.z_i = p.z_r * p.z_i;
		p.z_i += p.z_i + p.c_i;
		p.z_r = p.square_r - p.square_i + p.c_r;
		p.square_r = p.z_r * p.z_r;
		p.square_i = p.z_i * p.z_i;
	}
	if (p.iter != env->d.iter_max)
		ft_putpixel(env, x, y, env->d.colorp[p.iter]);
}

/*
** Render one frame when the env has changed.
*/

inline int			render(t_env *env)
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
		printf("\nx1 = %f\ty1 = %f\tc_i = %f\tstep = %f\nx2 = %f\ty2 = %f\tc_r = %f\n",
		env->d.x1, env->d.y1, env->d.c_i, env->d.step, env->d.x2, env->d.y2, env->d.c_r);
	}
	return (0);
}
