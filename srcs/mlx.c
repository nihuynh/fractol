/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/01 17:14:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

/*
** Handle the image business.
*/

void	ft_putpixel(t_env *env, int x, int y, int color)
{
	if (ft_btw(x, 0, env->win_w - 1) && ft_btw(y, 0, env->win_h - 1))
		env->imgstr[x + env->win_w * y] = color;
}

void	process_pixel(t_env *env, int x, int y)
{
	int		iter;
	double	c_r;
	double	c_i;
	double	z_r;
	double	z_i;
	double	square_r;
	double	square_i;

	iter = -1;
	z_r = 0;
	z_i = 0;
	c_r = env->x1 + (double)x * env->step_x;
	c_i = env->y1 + (double)y * env->step_y;
	square_r = z_r * z_r;
	square_i = z_i * z_i;
	while (++iter < env->iter_max && (square_r + square_i) <= 4.0)
	{
		z_i = z_r * z_i;
		z_i += z_i + c_i;
		z_r = square_r - square_i + c_r;
		square_r = z_r * z_r;
		square_i = z_i * z_i;
	}
	if (iter != env->iter_max)
		ft_putpixel(env, x, y, iter * 255 / env->iter_max << 8);
}

int		is_env_changed(t_env *env)
{
	if (env->x1 != env->old_x1 || env->x2 != env->old_x2
		|| env->y1 != env->old_y1 || env->y2 != env->old_y2
		|| env->iter_max != env->old_iter_max)
	{
		env->old_x1 = env->x1;
		env->old_x2 = env->x2;
		env->old_y1 = env->y1;
		env->old_y2 = env->y2;
		env->old_iter_max = env->iter_max;
		return (1);
	}
	return (0);
}

/*
** Render one frame when the env has changed.
*/

int		render(t_env *env)
{
	int i;
	int limit;

	i = -1;
	if (is_env_changed(env))
	{
		limit = env->win_w * env->win_h;
		mlx_clear_window(env->mlx, env->win);
		ft_bzero(env->imgstr, (limit * sizeof(int)));
		while (++i < limit)
			process_pixel(env, i % env->win_w, i / env->win_w);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		printf("\nx1 = %g\tx2 = %g\tstep_x = %g\ty1 = %g\ty2 = %g\tstep_y = %g
		\t\niter_max = %d", env->x1, env->x2, env->step_x, env->step_y, env->y1,
		env->y2, env->iter_max);
	}
	return (0);
}

void	quit_program(t_env *env, int exit_code)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	(exit_code == EXIT_SUCCESS) ? ft_putendl(MSG_BYE) : ft_putendl(MSG_ERR);
	(exit_code == EXIT_SUCCESS) ? exit(0) : ft_error(__func__, __LINE__);
}

/*
** Mlx handler.
*/

void	ft_new_window(t_env *env, int w, int h, char *title)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, w, h, title);
	env->img = mlx_new_image(env->mlx, w, h);
	env->imgstr = (int*)mlx_get_data_addr(env->img, &env->b, &env->s, &env->e);
	if (env->win == NULL)
		quit_program(env, EXIT_FAILURE);
	if (KEY_ENABLE)
		mlx_key_hook(env->win, deal_keyboard, (void*)env);
	if (MOUSE_ENABLE)
		mlx_mouse_hook(env->win, deal_mouse, (void*)env);
	render(env);
}
