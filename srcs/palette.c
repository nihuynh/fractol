/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/12 16:21:53 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

/*
** Choose the color for the pixel depending on the iteration & max iteration.
*/

inline int		palette(t_fractal data, int iter)
{
	float	t;
	int		rgb;

	if (data.palette == 0)
	{
		t = (float)iter / (float)data.iter_max;
		rgb = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
		rgb += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
		rgb += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		return (rgb);
	}
	return (iter * 255 / data.iter_max << data.rgb);
}

/*
** Print the command on the terminal when the key H is press.
*/

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

/*
** Handle the Head Up Display.
*/

inline void	show_hud(t_env *env, int time_frame)
{
	char *str;
	char *value;

	if (!(str = ft_strjoin("Mouse : ", ((env->motion_on == 1) ? "on" : "off"))))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 10, 16777215, str);
	free(str);
	if (!(value = ft_itoa(env->d.iter_max)))
		return ;
	str = ft_strjoin("Iteration : ", value);
	mlx_string_put(env->mlx, env->win, 15, 30, 16777215, str);
	free(value);
	free(str);
	if (!(value = ft_itoa(time_frame)))
		return ;
	str = ft_strjoin("Time(ms) : ", value);
	mlx_string_put(env->mlx, env->win, 15, 50, 16777215, str);
	free(value);
	free(str);
	if (!(value = ft_dtoa(env->d.c_r, 5)))
		return ;
	if (!(str = ft_strjoin("c_r : ", value)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 70, 16777215, str);
	free(value);
	free(str);
	if (!(value = ft_dtoa(env->d.c_i, 5)))
		return ;
	if (!(str = ft_strjoin("c_i : ", value)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 90, 16777215, str);
	free(value);
	free(str);
}