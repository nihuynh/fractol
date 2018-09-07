/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/07 04:26:55 by nihuynh          ###   ########.fr       */
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
	TYPE_Z toby[4];

	if (ft_btw(x, 0, VP_WIDTH) && ft_btw(y, 0, VP_HEIGHT))
	{
		x -= VP_WIDTH / 2;
		y -= VP_HEIGHT / 2;
		toby[0] = -x * env->d.step;
		toby[1] = -y * env->d.step;
		toby[2] = (env->d.x2 - env->d.x1) / value;
		toby[3] = (env->d.y2 - env->d.y1) / value;
		env->d.x1 += toby[2];
		env->d.x2 -= toby[2];
		env->d.y1 += toby[3];
		env->d.y2 -= toby[3];
		env->d.step = (env->d.x2 - env->d.x1) / (VP_WIDTH - 1);
		toby[0] += x * env->d.step;
		toby[1] += y * env->d.step;
		env->d.x1 -= toby[0];
		env->d.x2 -= toby[0];
		env->d.y1 -= toby[1];
		env->d.y2 -= toby[1];
		env->d.changed = 1;
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
	if (e->motion_on && ft_btw(x, 0, VP_WIDTH) && ft_btw(y, 0, VP_HEIGHT))
	{
		x -= VP_WIDTH / 2;
		y -= VP_HEIGHT / 2;
		if (x != e->old_x_mouse || y != e->old_y_mouse)
		{
			e->old_x_mouse = x;
			e->d.c_r = x * e->d.step;
			e->old_y_mouse = y;
			e->d.c_i = y * e->d.step;
			e->d.changed = 1;
		}
	}
	return (0);
}
