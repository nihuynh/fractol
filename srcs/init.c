/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:11:09 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/06 17:53:09 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

void	set_mandelbrot(t_env *env)
{
	env->type = MANDEL;
	env->x1 = M_XMIN;
	env->x2 = M_XMAX;
	env->win_w = VP_WIDTH;
	env->win_h = VP_HEIGHT;
	env->step = (env->x2 - env->x1) / (env->win_w - 1);
	env->y1 = -env->step * (env->win_h - 1) / 2;
	env->y2 = env->step * (env->win_h - 1) / 2;
	env->iter_max = ITER_MAX;
}

void	set_julia(t_env *env)
{
	env->type = JULIA;
	env->x1 = -J_X;
	env->x2 = J_X;
	env->c_r = 0.285;
	env->c_i = 0.01;
	env->win_w = VP_WIDTH;
	env->win_h = VP_HEIGHT;
	env->step = (env->x2 - env->x1) / (env->win_w - 1);
	env->y1 = -env->step * (env->win_h - 1) / 2;
	env->y2 = env->step * (env->win_h - 1) / 2;
	env->iter_max = ITER_MAX;
}
