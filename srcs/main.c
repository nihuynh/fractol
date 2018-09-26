/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:48 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/26 04:38:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

/*
** Clean exit.
*/

void				quit_program(t_env *env, int exit_code)
{
	int i;

	i = -1;
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	while (++i < C_THR)
		free(env->s[i].data);
	if (env->d.colorp != NULL)
		free(env->d.colorp);
	free(env);
	(exit_code == EXIT_SUCCESS) ? ft_putendl(MSG_BYE) : ft_putendl(MSG_ERR);
	while (DEBUG_LEAK)
		;
	(exit_code == EXIT_SUCCESS) ? exit(0) : ft_error(__func__, __LINE__);
}

static inline int	close_prg(t_env *env)
{
	quit_program(env, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

/*
** Mlx handler.
*/

static inline void	ft_new_window(t_env *env, int w, int h, char *title)
{
	mt_init(env);
	palalloc(env, &env->d);
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, w, h, title);
	env->img = mlx_new_image(env->mlx, w, h);
	env->imgstr = (int*)mlx_get_data_addr(env->img, &env->b, &env->w, &env->e);
	if (env->win == NULL)
		quit_program(env, EXIT_FAILURE);
	mlx_do_key_autorepeaton(env->mlx);
	mlx_hook(env->win, 2, 0, deal_keyboard, env);
	mlx_hook(env->win, 4, 0, deal_mouse, env);
	mlx_hook(env->win, 6, (1L << 6), mouse_motion, env);
	mlx_hook(env->win, 17, 1L << 17, close_prg, env);
	mlx_loop_hook(env->mlx, &render, env);
}

inline static void	fractal_picker(char *arg, t_env *env, int ac)
{
	if (ac == 1 || ft_strcasecmp(arg, "mandelbrot") == 0)
		set_mandelbrot(&env->d);
	else if (ft_strcasecmp(arg, "julia") == 0)
		set_julia(&env->d);
	else if (ft_strcasecmp(arg, "burning") == 0)
		set_burning(&env->d);
	else if (ft_strcasecmp(arg, "burnlia") == 0)
		set_burnlia(&env->d);
	else
	{
		ft_putendl(MSG_USAGE);
		free(env);
		exit(1);
	}
}

int					main(int ac, char **av)
{
	t_env	*env;

	if (ac > 2)
		ft_putendl(MSG_USAGE);
	else
	{
		if (!(env = (t_env*)ft_memalloc(sizeof(t_env))))
			ft_error(__func__, __LINE__);
		fractal_picker(av[1], env, ac);
		env->hud_cmd = 20;
		ft_new_window(env, VP_WIDTH, VP_HEIGHT, WIN_TITLE);
		mlx_loop(env->mlx);
		quit_program(env, EXIT_SUCCESS);
	}
	ft_putendl("Created by Nicolas Huynh @42 09/2018");
	return (0);
}
