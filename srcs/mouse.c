/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/04 20:58:31 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

/*
** Handle mouse events.
*/

int		deal_mouse(int mouse_code, t_env *env)
{
	if (mouse_code == 2)
		ft_putstr("\nRight click");
	else if (mouse_code == 1)
		ft_putstr("\nLeft click");
	else if (mouse_code == 5)
		ft_putstr("\nScroll up");
	else if (mouse_code == 4)
		ft_putstr("\nScroll down");
	else if (DEBUG)
		ft_print_value("\nMouse event : ", mouse_code);
	(void)env;
	return (0);
}

int		mouse_motion(int x, int y, t_env *e)
{
	if (e->motion_on == 0)
		return (0);
	if (e->type == JULIA && ft_btw(x, 0, e->win_w) && ft_btw(y, 0, e->win_h))
	{
		x -= e->win_w / 2;
		y -= e->win_h / 2;
		if (x != e->old_x_mouse)
		{
			ft_print_value("\nMouse x : ", x);
			e->old_x_mouse = x;
			e->c_r = x * e->step_x;
		}
		if (y != e->old_y_mouse)
		{
			ft_print_value("\nMouse y : ", y);
			e->old_y_mouse = y;
			e->c_i = y * e->step_y;
		}
	}
	return (0);
}
