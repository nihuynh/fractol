/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/07 19:12:19 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

/*
** toby[0] <==> c_r;
** toby[1] <==> c_i;
** toby[2] <==> dx;
** toby[3] <==> dy;
*/

static inline void	zoom_on(t_fractal *data, int value, int x, int y)
{
	TYPE_Z toby[4];

	if (ft_btw(x, 0, VP_WIDTH) && ft_btw(y, 0, VP_HEIGHT))
	{
		x -= VP_WIDTH / 2;
		y -= VP_HEIGHT / 2;
		toby[0] = -x * data->step;
		toby[1] = -y * data->step;
		toby[2] = (data->x2 - data->x1) / value;
		toby[3] = (data->y2 - data->y1) / value;
		data->x1 += toby[2];
		data->x2 -= toby[2];
		data->y1 += toby[3];
		data->y2 -= toby[3];
		data->step = (data->x2 - data->x1) / (VP_WIDTH - 1);
		toby[0] += x * data->step;
		toby[1] += y * data->step;
		data->x1 -= toby[0];
		data->x2 -= toby[0];
		data->y1 -= toby[1];
		data->y2 -= toby[1];
		data->changed = 1;
	}
}

/*
** Handle mouse events.
*/

int		deal_mouse(int mouse_code, int x, int y, t_env *env)
{
	if (mouse_code == 2)
		ft_putstr("\nRight click");
	else if (mouse_code == 1)
		ft_putstr("\nLeft click");
	else if (mouse_code == 5)
		zoom_on(&env->d, 25, x, y);
	else if (mouse_code == 4)
		zoom_on(&env->d, -25, x, y);
	else if (DEBUG)
		ft_print_value("\nMouse event : ", mouse_code);
	return (0);
}

int		mouse_motion(int x, int y, t_env *env)
{
	if (env->motion_on && ft_btw(x, 0, VP_WIDTH) && ft_btw(y, 0, VP_HEIGHT))
	{
		if (x != env->old_x_mouse || y != env->old_y_mouse)
		{
			env->old_x_mouse = x;
			env->d.c_r = env->d.x1 + x * env->d.step;
			env->old_y_mouse = y;
			env->d.c_i = env->d.y1 + y * env->d.step;
			env->d.changed = 1;
		}
	}
	return (0);
}
