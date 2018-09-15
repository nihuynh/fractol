/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/14 23:38:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
	t_pxl pxl;

	iter_julbrot(env, &pxl, x, y);
	if (pxl.iter != env->d.iter_max)
		ft_putpixel(env, x, y, env->d.colorp[pxl.iter]);
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
		palalloc(env, &env->d);
		while (++i < limit)
			process_pixel(env, i % VP_WIDTH, i / VP_WIDTH);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		time_frame = clock() - start;
		show_hud(env, (int) time_frame/1000);
	}
	return (0);
}
