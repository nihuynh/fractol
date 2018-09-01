/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:48 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/01 18:01:43 by nihuynh          ###   ########.fr       */
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
	if (env->win == NULL)
		quit_program(env, EXIT_FAILURE);
	if (KEY_ENABLE)
		mlx_key_hook(env->win, deal_keyboard, (void*)env);
	if (MOUSE_ENABLE)
		mlx_mouse_hook(env->win, deal_mouse, (void*)env);
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
		set_mandelbrot(env);
		ft_new_window(env, env->win_w, env->win_h, WIN_TITLE);
		mlx_loop_hook(env->mlx, &render, env);
		mlx_loop(env->mlx);
		quit_program(env, EXIT_SUCCESS);
	}
	return (0);
}
