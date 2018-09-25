/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:57:03 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/25 19:30:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "libft.h"
#include <time.h>

static inline void	apply_palette(t_env *env)
{
	int		ndx;
	int		cslice;
	int		xslice;
	int		pxl_iter;

	ndx = -1;
	cslice = -1;
	while (++ndx < env->vp_len)
	{
		xslice = ndx % env->s_len;
		if (xslice == 0)
			cslice++;
		pxl_iter = env->s[cslice].data[xslice].iter;
		if (pxl_iter >= env->d.iter_max || pxl_iter < 0)
			env->imgstr[ndx] = 0;
		else
			env->imgstr[ndx] = env->d.colorp[pxl_iter];
	}
}

/*
** Render one frame when the env has changed.
*/

inline int			render(t_env *env)
{
	clock_t	start;
	clock_t	time_frame;
	int		i;

	i = -1;
	if (env->d.changed || env->d.new_pal)
	{
		start = clock();
		if (env->d.iter_max <= 0)
			env->d.iter_max = ITER_MAX;
		env->d.changed = 0;
		mt_render(env);
		ft_bzero(env->imgstr, (env->vp_len * sizeof(int)));
		if (env->d.new_pal)
			palalloc(env, &env->d);
		apply_palette(env);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		time_frame = clock() - start;
		show_hud(env, (int)time_frame / 1000);
	}
	return (0);
}
