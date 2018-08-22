/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/08/23 01:57:03 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

/*
** Handle the image business.
*/

void	ft_putpixel(t_env *env, int x, int y, int color)
{
	if (ft_btw(x, 0, WIN_WIDTH) && ft_btw(y, 0 , WIN_HEIGHT))
		env->imgstr[x + WIN_WIDTH * y] = color;
}

void    quit_program(t_env *env, int exit_code)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
    (exit_code == EXIT_SUCCESS) ? ft_putendl(MSG_BYE) : ft_putendl(MSG_ERR);
	(exit_code == EXIT_SUCCESS) ? exit(0) : ft_error(__func__, __LINE__);
}

/*
** Handle mouse events.
*/

int     deal_mouse(int mouse_code, t_env *env)
{
	if (DEBUG)
	{
		if (mouse_code == 2)
			ft_putstr("\nRight click");
		else if (mouse_code == 1)
			ft_putstr("\nLeft click");
		else
			ft_print_value("\nMouse event : ", mouse_code);
	}
	(void)env;
	return (0);
}

/*
** Handle keyboard events.
*/

int     deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_SYS_OUT)
		quit_program(env, EXIT_SUCCESS);
	if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}

/*
** Mlx handler.
*/

void    ft_new_window(t_env *env, int h, int w, char *title)
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
	env->zoom = 100;
}
