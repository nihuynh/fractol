/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/01 18:07:46 by nihuynh          ###   ########.fr       */
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

void	set_iter(t_env *env, int value)
{
	env->iter_max += value;
}

/*
** Handle keyboard events.
*/

int		deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_SYS_OUT)
		quit_program(env, EXIT_SUCCESS);
	else if (key_code == 14)
		zoom(env, 4);
	else if (key_code == 12)
		zoom(env, -4);
	else if (key_code == 123)
		translate(env, -3, 1);
	else if (key_code == 124)
		translate(env, 3, 1);
	else if (key_code == 125)
		translate(env, 3, 0);
	else if (key_code == 126)
		translate(env, -3, 0);
	else if (key_code == 15)
		set_iter(env, 10);
	else if (key_code == 3)
		set_iter(env, -10);
	else if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}
