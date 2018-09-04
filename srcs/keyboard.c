/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/04 21:01:44 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

void	zoom(t_env *env, double value)
{
	double dx;
	double dy;

	dx = (env->x2 - env->x1) / value;
	dy = (env->y2 - env->y1) / value;
	env->x1 += dx;
	env->x2 -= dx;
	env->y1 += dy;
	env->y2 -= dy;
	env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
	env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
}

void	translate(t_env *env, double value, int is_x)
{
	double dx;
	double dy;

	dx = (env->x2 - env->x1) / value;
	dy = (env->y2 - env->y1) / value;
	if (is_x)
	{
		env->x1 += dx;
		env->x2 += dx;
	}
	else
	{
		env->y1 += dy;
		env->y2 += dy;
	}
	env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
	env->step_y = (env->y2 - env->y1) / (env->win_h - 1);
}

void	key_translate(t_env *env, int key_code)
{
	if (key_code == 123)
		translate(env, -20, 1);
	else if (key_code == 124)
		translate(env, 20, 1);
	else if (key_code == 125)
		translate(env, 20, 0);
	else if (key_code == 126)
		translate(env, -20, 0);
}

void	set_fractal(t_env *env)
{
	env->type += (env->type == 1) ? -1 : 1;
	if (env->type == JULIA)
		set_julia(env);
	if (env->type == MANDEL)
		set_mandelbrot(env);
}

/*
** Handle keyboard events.
*/

int		deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_SYS_OUT)
		quit_program(env, EXIT_SUCCESS);
	else if (key_code == 14)
		zoom(env, 20);
	else if (key_code == 12)
		zoom(env, -20);
	else if (key_code == ft_btw(key_code, 123, 126))
		key_translate(env, key_code);
	else if (key_code == 15)
		env->iter_max += 10;
	else if (key_code == 3)
		env->iter_max += -10;
	else if (key_code == 0)
		env->rgb += (env->rgb == 22) ? -22 : 2;
	else if (key_code == 1)
		env->palette += (env->palette == 1) ? -1 : 1;
	else if (key_code == 49)
		env->motion_on += (env->motion_on == 1) ? -1 : 1;
	else if (key_code == 48)
		set_fractal(env);
	else if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}
