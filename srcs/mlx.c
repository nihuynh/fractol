/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/22 16:07:46 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
** Render one frame when the env has changed.
*/

inline int			render(t_env *env)
{
	clock_t	start;
	clock_t	time_frame;
	int		i;
	int		limit;

	i = -1;
	if (env->d.changed || env->d.new_pal)
	{
		start = clock();
		env->d.changed = 0;
		if (env->d.new_pal)
			palalloc(env, &env->d);
		limit = VP_WIDTH * VP_HEIGHT;
		ft_bzero(env->imgstr, (limit * sizeof(int)));
		mt_render(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		time_frame = clock() - start;
		show_hud(env, (int)time_frame / 1000);
	}
	return (0);
}
