/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/05 11:51:29 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

void	zoom_on(t_env *env, int value, int x, int y)
{
	if (ft_btw(x, 0, env->win_w) && ft_btw(y, 0, env->win_h))
	{
		x -= env->win_w / 2;
		y -= env->win_h / 2;
		env->x1 += (x * env->step_x + (env->x2 - env->x1) / value);
		env->x2 += (x * env->step_x - (env->x2 - env->x1) / value);
		env->y1 += (y * env->step_y + (env->y2 - env->y1) / value);
		env->y2 += (y * env->step_y - (env->y2 - env->y1) / value);
		env->step_x = (env->x2 - env->x1) / (env->win_w - 1);
		env->step_y = env->step_x;
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
		ft_print_value("\nMouse X : ", x);
		ft_print_value("\nMouse Y : ", y);
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
			e->c_r = x * e->step_x;
		}
		if (y != e->old_y_mouse)
		{
			e->old_y_mouse = y;
			e->c_i = y * e->step_y;
		}
	}
	return (0);
}
