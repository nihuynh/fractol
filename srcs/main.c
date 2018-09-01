/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:48 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/01 17:12:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

int	main(int ac, char **av)
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
