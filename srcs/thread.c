/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:34:45 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/21 03:40:58 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

/*
** Handle the image business.
*/

static inline void	ft_putpixel(t_env *env, int x, int y, int color)
{
	if (ft_btw(x, 0, VP_WIDTH - 1) && ft_btw(y, 0, VP_HEIGHT - 1))
		env->imgstr[x + VP_WIDTH * y] = color;
}

void				mt_init(t_env *env)
{
	int i;

	i = -1;
	while (++i < C_THR)
	{
		env->s[i].id = i;
		env->s[i].env = env;
		if (!(env->s[i].data = ft_memalloc(sizeof(t_pxl) * SLICE_LEN)))
			quit_program(env, EXIT_FAILURE);
	}
}

static inline void	process_pixel(t_env *env, int ndx, int y)
{
	int x;
	t_pxl pxl;

	x = ndx % VP_WIDTH;
	iter_julbrot(env, &pxl, x, y);
	if (pxl.iter == env->d.iter_max || pxl.iter < 0)
		ft_putpixel(env, x, y, 0);
	else
		ft_putpixel(env, x, y, env->d.colorp[pxl.iter]);
}

static inline void	*compute(void *arg)
{
	t_slice	*slice;
	t_env	*env;
	int		i;
	int		ofs;

	slice = arg;
	env = slice->env;
	ofs = slice->id * PXL_HEIGHT;
	i = -1;
	ft_bzero(slice->data, sizeof(t_pxl) * SLICE_LEN);
	while (++i < SLICE_LEN)
		process_pixel(env, i, ofs + i / VP_WIDTH);
	//printf("Thread id : %d y1 = %f y1 = %f\n", slice->id, slice->y1, slice->y2);
	//printf("Env hud : %d fmaxiter = %d\n", env->hud_on, env->d.iter_max);
	return (NULL);
}

int					mt_render(t_env *env)
{
	int			cthr;
	int			sats;
	void		*ptr;
	pthread_t	toby[C_THR];

	cthr = -1;
	sats = 0;
	while (++cthr < C_THR && !sats)
	{
		ptr = &(env->s[cthr]);
		sats = pthread_create(&toby[cthr], NULL, compute, ptr);
	}
	cthr = -1;
	while (++cthr < C_THR)
		pthread_join(toby[cthr], NULL);
	return (EXIT_SUCCESS);
}
