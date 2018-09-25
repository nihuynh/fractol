/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 13:03:17 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/25 13:03:17 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	data->x1 = -3;
	data->x2 = 3;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2;
	if (data->iter_max != ITER_MAX)
		data->new_pal = 1;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}
