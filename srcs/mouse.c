/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 22:38:15 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"

/*
** The function save the position of the mouse on the complex plane.
** It then zoom and translate the frame to match the position of the mouse.
** toby[0] <==> c_r;
** toby[1] <==> c_i;
** toby[2] <==> dx;
** toby[3] <==> dy;
*/

static inline void	zoom_on_cursor(t_fractal *data, int value, int x, int y)
{
	TYPE_Z toby[4];

	if (ft_btw(x, 0, VP_WIDTH) && ft_btw(y - 20, 0, VP_HEIGHT))
	{
		data->reiter = 0;
		x -= VP_WIDTH / 2;
		y -= VP_HEIGHT / 2;
		toby[0] = -x * data->step;
		toby[1] = -y * data->step;
		toby[2] = (data->x2 - data->x1) / value;
		toby[3] = (data->y2 - data->y1) / value;
		data->x1 += toby[2];
		data->x2 -= toby[2];
		data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
		toby[0] += x * data->step;
		toby[1] += y * data->step;
		data->x1 -= toby[0];
		data->x2 -= toby[0];
		data->y1 += toby[3] - toby[1];
		data->y2 -= toby[3] + toby[1];
		data->changed = 1;
	}
}

/*
** Handle mouse clicks and scrolls.
*/

int					deal_mouse(int mouse_code, int x, int y, t_env *env)
{
	if (env->d.type % 2 == MANDEL && mouse_code == 1)
	{
		env->motion_on = 1;
		mouse_motion(x, y, env);
		env->motion_on = 0;
		if (env->d.type == MANDEL)
			set_julia(&env->d, JULIA);
		if (env->d.type == BURNING)
			set_julia(&env->d, BURNING_JULIA);
		if (env->d.type == SYM)
			set_julia(&env->d, SYM_JULIA);
	}
	else if (mouse_code == 5)
		zoom_on_cursor(&env->d, 25, x, y);
	else if (mouse_code == 4)
		zoom_on_cursor(&env->d, -25, x, y);
	else if (DEBUG)
		ft_print_value("\nMouse event : ", mouse_code);
	return (0);
}

/*
** This changing the fractal c_r, c_i base on the mouse position.
*/

inline int			mouse_motion(int x, int y, t_env *env)
{
	if (env->motion_on && ft_btw(x, 0, VP_WIDTH) && ft_btw(y, 0, VP_HEIGHT))
	{
		if (x != env->old_x_mouse || y != env->old_y_mouse)
		{
			env->d.reiter = 0;
			env->old_x_mouse = x;
			env->d.c_r = env->d.x1 + x * env->d.step;
			env->old_y_mouse = y;
			env->d.c_i = env->d.y1 + y * env->d.step;
			env->d.changed = 1;
		}
	}
	return (0);
}
