/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:48 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/05 11:25:17 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

void				quit_program(t_env *env, int exit_code)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	(exit_code == EXIT_SUCCESS) ? ft_putendl(MSG_BYE) : ft_putendl(MSG_ERR);
	(exit_code == EXIT_SUCCESS) ? exit(0) : ft_error(__func__, __LINE__);
}

/*
** Mlx handler.
*/

static inline void	ft_new_window(t_env *env, int w, int h, char *title)
{
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, w, h, title);
	env->img = mlx_new_image(env->mlx, w, h);
	env->imgstr = (int*)mlx_get_data_addr(env->img, &env->b, &env->s, &env->e);
	mlx_do_key_autorepeaton(env->mlx);
	if (env->win == NULL)
		quit_program(env, EXIT_FAILURE);
	if (KEY_ENABLE)
		mlx_hook(env->win, 2, 0, deal_keyboard, env);
	if (MOUSE_ENABLE)
	{
		mlx_hook(env->win, 4, 0, deal_mouse, env);
		mlx_hook(env->win, 6, (1L << 6), mouse_motion, env);
	}
	render(env);
}

int					main(int ac, char **av)
{
	t_env	*env;

	if (ac != 2)
		ft_putendl(MSG_USAGE);
	else
	{
		ft_putendl(av[1]);
		if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
			ft_error(__func__, __LINE__);
		if (ft_strcasecmp(av[1], "mandelbrot") == 0)
			set_mandelbrot(env);
		if (ft_strcasecmp(av[1], "julia") == 0)
			set_julia(env);
		ft_new_window(env, env->win_w, env->win_h, WIN_TITLE);
		show_help();
		mlx_loop_hook(env->mlx, &render, env);
		mlx_loop(env->mlx);
		quit_program(env, EXIT_SUCCESS);
	}
	return (0);
}
