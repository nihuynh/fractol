/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:54 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/19 00:54:36 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

#ifndef __APPLE__
# include "keycode_linux.h"
#else
# include "keycode_mac.h"
#endif

static inline void	zoom(t_fractal *data, TYPE_Z value)
{
	TYPE_Z dx;
	TYPE_Z dy;

	data->reiter = 0;
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

	data->reiter = 0;
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

static inline void	key_part_one(t_fractal *data, int key_code)
{
	if (key_code == KEY_LEFT)
		translate(data, 20 * INVERSE_M, 1, 0);
	else if (key_code == KEY_RIGHT)
		translate(data, -20 * INVERSE_M, 1, 0);
	else if (key_code == KEY_DOWN)
		translate(data, -20 * INVERSE_M, 0, 1);
	else if (key_code == KEY_UP)
		translate(data, 20 * INVERSE_M, 0, 1);
	else if (key_code == KEY_1)
		set_mandelbrot(data);
	else if (key_code == KEY_2)
		set_julia(data);
	else if (key_code == KEY_3)
		set_burning(data);
	else if (key_code == KEY_4)
		set_burnlia(data);
}

static inline void	key_part_two(t_fractal *data, int key_code)
{
	if (key_code == KEY_R && (data->new_pal = 1))
		data->iter_max += 50;
	else if (key_code == KEY_F && (data->new_pal = 1))
		data->iter_max -= (data->iter_max <= 50) ? 0 : 50;
	else if (key_code == KEY_T && (data->new_pal = 1))
		data->iter_max += 5;
	else if (key_code == KEY_G && (data->new_pal = 1))
		data->iter_max -= (data->iter_max <= 5) ? 0 : 5;
	else if (key_code == KEY_E)
		zoom(data, 20);
	else if (key_code == KEY_Q)
		zoom(data, -20);
}

/*
** Handle keyboard events.
*/

int					deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_ESCAPE)
		quit_program(env, EXIT_SUCCESS);
	key_part_one(&env->d, key_code);
	key_part_two(&env->d, key_code);
	if (key_code == KEY_H && (env->d.changed = 1))
		env->hud_on += (env->hud_on == 1) ? -1 : 1;
	else if (key_code == KEY_SPACEBAR && (env->d.changed = 1))
		env->motion_on += (env->motion_on == 1) ? -1 : 1;
	else if (key_code == KEY_P && (env->d.new_pal = 1))
		env->type_palette += (env->type_palette == C_PALETTE) ? -C_PALETTE : 1;
	else if (key_code == KEY_C && (env->d.changed = 1))
		env->hud_cmd = (env->hud_cmd > 0) ? 0 : 20;
	else if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}
