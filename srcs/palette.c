/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/14 20:06:56 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

/*
** Choose the color for the pixel depending on the iteration & max iteration.
*/

inline void		palalloc(t_env *env, t_fractal *f)
{
	float	t;
	int		i;

 	i = -1;
	if (f->colorp != NULL)
		free(f->colorp);
	if (!(f->colorp = ft_memalloc(f->iter_max * sizeof(int))))
		quit_program(env, EXIT_FAILURE);
	while (++i < f->iter_max)
	{
		t = (float)i / (float)f->iter_max;
		f->colorp[i] = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
		f->colorp[i] += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
		f->colorp[i] += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	}
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