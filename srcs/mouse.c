/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 23:10:43 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/03 17:17:27 by nihuynh          ###   ########.fr       */
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

int		mouse_motion(int mouse_code, t_env *env)
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
