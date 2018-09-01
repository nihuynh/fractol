/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:11:09 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/01 17:05:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

void	set_mandelbrot(t_env *env)
{
	env->x1 = -2.15;
	env->x2 = 0.65;
	env->y1 = -1.25;
	env->y2 = 1.25;
	env->win_w = 1050;
	env->win_h = 960;
	env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
	env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
	env->iter_max = ITER_MAX;
}
