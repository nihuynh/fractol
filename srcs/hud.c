/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:29:23 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/22 15:37:33 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"
#include "mlx.h"
#include <stdlib.h>

static inline void	hud_mouse(t_env *env)
{
	char	*val;

	if (!(val = ft_strdup((env->motion_on == 1) ? "on" : "off")))
		return ;
	mlx_string_put(env->mlx, env->win, 15, 10, 16777215, "Mouse : ");
	mlx_string_put(env->mlx, env->win, 95, 10, 16777215, val);
	free(val);
}

static inline void	hud_value(t_env *env, int value, char *str, int pos)
{
	char	*val;
	int		xv;
	int		yv;

	yv = 10 + pos * 20;
	xv = 15 + ft_strlen(str) * 10;
	if (!(val = ft_itoa(value)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, yv, 16777215, str);
	mlx_string_put(env->mlx, env->win, xv, yv, 16777215, val);
	free(val);
}

static inline void	hud_dvalue(t_env *env, double value, char *str, int pos)
{
	char	*val;
	int		xv;
	int		yv;

	yv = 10 + pos * 20;
	xv = 15 + ft_strlen(str) * 10;
	if (!(val = ft_dtoa(value, DTOA_DSCP)))
		return ;
	mlx_string_put(env->mlx, env->win, 15, yv, 16777215, str);
	mlx_string_put(env->mlx, env->win, xv, yv, 16777215, val);
	free(val);
}

/*
** Handle the Head Up Display.
*/

void				show_hud(t_env *env, int time_frame)
{
	if (env->hud_on)
	{
		hud_mouse(env);
		hud_value(env, env->d.iter_max, "Iteration : ", 1);
		hud_value(env, time_frame, "Time(ms) : ", 2);
		hud_dvalue(env, env->d.c_r, "c_r : ", 3);
		hud_dvalue(env, env->d.c_i, "c_i : ", 4);
		hud_dvalue(env, env->d.x1, "x1 : ", 6);
		hud_dvalue(env, env->d.x2, "x2 : ", 7);
		hud_dvalue(env, env->d.y1, "y1 : ", 8);
		hud_dvalue(env, env->d.y2, "y2 : ", 9);
		hud_dvalue(env, env->d.step, "step : ", 10);
	}
}
