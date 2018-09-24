/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/24 12:45:38 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

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

/*
** Handle keyboard events.
*/

int					deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_SYS_OUT)
		quit_program(env, EXIT_SUCCESS);
	if (key_code == 4 && show_help() && (env->d.changed = 1))
		env->hud_on += (env->hud_on == 1) ? -1 : 1;
	if (key_code == 14)
		zoom(&env->d, 20);
	else if (key_code == 12)
		zoom(&env->d, -20);
	else if (ft_btw(key_code, 123, 126))
		key_translate(&env->d, key_code);
	else if (key_code == 15 && (env->d.new_pal = 1))
		env->d.iter_max += 50;
	else if (key_code == 3 && (env->d.new_pal = 1))
		env->d.iter_max -= (env->d.iter_max == 50) ? 0 : 50;
	else if (key_code == 49 && (env->d.changed = 1))
		env->motion_on += (env->motion_on == 1) ? -1 : 1;
	else if (key_code == 257 && (env->d.new_pal = 1))
		env->cshift += (env->cshift == 5) ? -5 : 1;
	else if (key_code == 35 && (env->d.new_pal = 1))
		env->ctype += (env->ctype == 2) ? -2 : 1;
	else if (key_code == 18)
		set_mandelbrot(&env->d);
	else if (key_code == 19)
		set_julia(&env->d);
	else if (key_code == 20)
		set_burning(&env->d);
	else if (key_code == 21)
		set_burnlia(&env->d);
	else if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}
