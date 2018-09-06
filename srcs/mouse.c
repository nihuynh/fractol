/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/06 17:52:31 by nihuynh          ###   ########.fr       */
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

void	zoom_on(t_env *env, int value, int x, int y)
{
	double toby[4];

	if (ft_btw(x, 0, env->win_w) && ft_btw(y, 0, env->win_h))
	{
		x -= env->win_w / 2;
		y -= env->win_h / 2;
		toby[0] = -x * env->step;
		toby[1] = -y * env->step;
		toby[2] = (env->x2 - env->x1) / value;
		toby[3] = (env->y2 - env->y1) / value;
		env->x1 += toby[2];
		env->x2 -= toby[2];
		env->y1 += toby[3];
		env->y2 -= toby[3];
		env->step = (env->x2 - env->x1) / (env->win_w - 1);
		toby[0] += x * env->step;
		toby[1] += y * env->step;
		env->x1 -= toby[0];
		env->x2 -= toby[0];
		env->y1 -= toby[1];
		env->y2 -= toby[1];
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
		zoom_on(env, 25, x, y);
	else if (mouse_code == 4)
		zoom_on(env, -25, x, y);
	else if (DEBUG)
	{
		ft_print_value("\nMouse event : ", mouse_code);
		ft_print_value("\tMouse X : ", x);
		ft_print_value("\tMouse Y : ", y);
	}
	return (0);
}

int		mouse_motion(int x, int y, t_env *e)
{
	if (e->motion_on && ft_btw(x, 0, e->win_w) && ft_btw(y, 0, e->win_h))
	{
		x -= e->win_w / 2;
		y -= e->win_h / 2;
		if (x != e->old_x_mouse)
		{
			e->old_x_mouse = x;
			e->c_r = x * e->step;
		}
		if (y != e->old_y_mouse)
		{
			e->old_y_mouse = y;
			e->c_i = y * e->step;
		}
	}
	return (0);
}
