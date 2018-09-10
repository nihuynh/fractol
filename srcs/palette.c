/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/11 00:49:47 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

inline int		palette(t_fractal data, int iter)
{
	float	t;
	int		rgb;

	if (data.palette == 1)
		return (iter * 255 / data.iter_max << data.rgb);
	t = (float)iter / (float)data.iter_max;
	rgb = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
	rgb += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
	rgb += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (rgb);
}

inline void	show_help(void)
{
	ft_putendl("\n\n\n\n\n\n\n\n\n");
	ft_putendl("Q to zoom out & E to zoom in");
	ft_putendl("A to change the rgb & S for the palette");
	ft_putendl("R to increase the iteration & F to decrease it");
	ft_putendl("TAB to change the fractal");
	ft_putendl("SPACE to lock the mouse_motion");
	ft_putendl("Arrow to move & ESC to quit");
}

inline void	show_hud(t_env *env, int time_frame)
{
	char *str;
	char *value;

	str = ft_strjoin("Mouse : ", ((env->motion_on == 1) ? "on" : "off"));
	mlx_string_put(env->mlx, env->win, 15, 10, 16777215, str);
	free(str);
	value = ft_itoa(env->d.iter_max);
	str = ft_strjoin("Iteration : ", value);
	mlx_string_put(env->mlx, env->win, 15, 30, 16777215, str);
	free(value);
	free(str);
	value = ft_itoa(time_frame);
	str = ft_strjoin("Time(ms) : ", value);
	mlx_string_put(env->mlx, env->win, 15, 50, 16777215, str);
	free(value);
	free(str);
}