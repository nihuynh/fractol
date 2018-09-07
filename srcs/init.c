/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:11:09 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/07 04:29:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

/*
** This set/reset the parameter of the fractal.
** It also center the origin of the complex plane.
*/

void	set_mandelbrot(t_fractal *data)
{
	data->type = MANDEL;
	data->x1 = M_XMIN;
	data->x2 = M_XMAX;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}

void	set_julia(t_fractal *data)
{
	data->type = JULIA;
	data->x1 = -J_X;
	data->x2 = J_X;
	data->c_r = 0.285;
	data->c_i = 0.01;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->y1 = -data->step * (VP_HEIGHT - 1) / 2;
	data->y2 = data->step * (VP_HEIGHT - 1) / 2;
	data->iter_max = ITER_MAX;
	data->changed = 1;
}
