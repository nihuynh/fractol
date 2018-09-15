/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/14 20:05:42 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

static inline void	zoom(t_fractal *data, TYPE_Z value)
{
	TYPE_Z dx;
	TYPE_Z dy;

	dx = (data->x2 - data->x1) / value;
	dy = (data->y2 - data->y1) / value;
	data->x1 += dx;
	data->x2 -= dx;
	data->y1 += dy;
	data->y2 -= dy;
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->changed = 1;
}

static inline void	translate(t_fractal *data, TYPE_Z value, int is_x, int is_y)
{
	TYPE_Z dx;
	TYPE_Z dy;

	dx = (data->x2 - data->x1) / value;
	dy = (data->y2 - data->y1) / value;
	if (is_x)
	{
		data->x1 += dx;
		data->x2 += dx;
	}
	if (is_y)
	{
		data->y1 += dy;
		data->y2 += dy;
	}
	data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
	data->changed = 1;
}

/*
** Handle the image business.
*/

static inline void	key_translate(t_fractal *data, int key_code)
{
	if (key_code == 123)
		translate(data, 20, 1, 0);
	else if (key_code == 124)
		translate(data, -20, 1, 0);
	else if (key_code == 125)
		translate(data, -20, 0, 1);
	else if (key_code == 126)
		translate(data, 20, 0, 1);
}

static inline void	set_fractal(t_fractal *data)
{
	data->type += (data->type == 1) ? -1 : 1;
	if (data->type == JULIA)
		set_julia(data);
	if (data->type == MANDEL)
		set_mandelbrot(data);
}

/*
** Handle keyboard events.
*/

int					deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_SYS_OUT)
		quit_program(env, EXIT_SUCCESS);
	if (key_code == 4)
		show_help();
	if (key_code == 14)
		zoom(&env->d, 20);
	else if (key_code == 12)
		zoom(&env->d, -20);
	else if (ft_btw(key_code, 123, 126))
		key_translate(&env->d, key_code);
	else if (key_code == 15 && (env->d.changed = 1))
		env->d.iter_max += 50;
	else if (key_code == 3 && (env->d.changed = 1))
		env->d.iter_max -= 50;
	else if (key_code == 49 && (env->d.changed = 1))
		env->motion_on += (env->motion_on == 1) ? -1 : 1;
	else if (key_code == 48)
		set_fractal(&env->d);
	else if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}
