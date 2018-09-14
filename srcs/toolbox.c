/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/14 16:45:18 by nihuynh          ###   ########.fr       */
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
		// t = sqrt((float)iter / (float)data.iter_max);
		t = (float)iter / (float)data.iter_max;
		rgb = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
		rgb += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
		rgb += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
		return (rgb);
	}
	return (iter * 255 / data.iter_max << data.rgb);
}

inline int		*palalloc(int iter_max)
{
	float	t;
	int		*res;
	int		i;

	i = -1;
	if (!(ft_memalloc(iter_max * sizeof(int))))
		quit_program(env, EXIT_FAILURE)
	while (++i < iter_max)
	{
		t = (float)i / (float)iter_max;
		res[i] = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
		res[i] += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
		res[i] += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
	return (res);
}

/*
** Print the command on the terminal when the key H is press.
*/

inline void	show_help(void)
{
	ft_putendl("\n\n\n\n\n\n\n\n\n");
	ft_putendl(USG_TYPE);
	ft_putendl(USG_ZOOM);
	ft_putendl(USG_ITER);
	ft_putendl(USG_COLR);
	ft_putendl(USG_ESCP);
}

/*
** Handle the Head Up Display.
*/

inline void	show_hud(t_env *env, int time_frame)
{
	char *value;

	if (!(value = ft_strdup((env->motion_on == 1) ? "on" : "off")))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 10, 16777215, "Mouse : ");
	mlx_string_put(env->mlx, env->win, 95, 10, 16777215, value);
	free(value);
	if (!(value = ft_itoa(env->d.iter_max)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 30, 16777215, "Iteration : ");
	mlx_string_put(env->mlx, env->win, 135, 30, 16777215, value);
	free(value);
	if (!(value = ft_itoa(time_frame)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 50, 16777215, "Time(ms) : ");
	mlx_string_put(env->mlx, env->win, 125, 50, 16777215, value);
	free(value);
	if (!(value = ft_dtoa(env->d.c_r, 5)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 70, 16777215, "c_r : ");
	mlx_string_put(env->mlx, env->win, 75, 70, 16777215, value);
	free(value);
	if (!(value = ft_dtoa(env->d.c_i, 5)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 90, 16777215, "c_i : ");
	mlx_string_put(env->mlx, env->win, 75, 90, 16777215, value);
	free(value);
}