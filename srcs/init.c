/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:11:09 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/04 20:38:51 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

void	set_mandelbrot(t_env *env)
{
	env->type = MANDEL;
	env->x1 = -2.1;
	env->x2 = 0.6;
	env->y1 = -1.2;
	env->y2 = 1.2;
	env->win_w = 1350;
	env->win_h = 1200;
	env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
	env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
	env->iter_max = ITER_MAX;
	ft_print_value("win_w : ", env->win_w);
	ft_print_value("win_h : ", env->win_h);
}

void	set_julia(t_env *env)
{
	env->type = JULIA;
	env->x1 = -1.80;
	env->x2 = 1.80;
	env->y1 = -1.5;
	env->y2 = 1.5;
	env->c_r = 0.285;
	env->c_i = 0.01;
	env->win_w = 1350;
	env->win_h = 1200;
	env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
	env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
	env->iter_max = ITER_MAX;
	ft_print_value("win_w : ", env->win_w);
	ft_print_value("win_h : ", env->win_h);
}
