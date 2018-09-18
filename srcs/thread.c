/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:34:45 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/17 22:36:25 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void				mt_init(t_env *env)
{
	int i;

	i = -1;
	while (++i < CTHR)
	{
		env->s[i].y1 = env->d.y1 + i * (env->d.y2 - env->d.y1) / CTHR;
		env->s[i].y2 = env->d.y1 + (i + 1) * (env->d.y2 - env->d.y1) / CTHR	;
		if (!(env->s[i].data = ft_memalloc(sizeof(t_pxl) * SLICE_LEN)))
			quit_program(env, EXIT_FAILURE);
	}
}

static inline void	*compute(void *arg)
{
	t_env *env;

	env = arg;
	ft_print_value("\nSuper String : ", env->d.iter_max);
	return (NULL);
}

inline int			mt_render(t_env *env)
{
	intptr_t	cthr;
	int			status;
	pthread_t	toby[CTHR];

	cthr = 0;
	status = 0;
	while (cthr < CTHR && !status)
	{
		status = pthread_create(&toby[cthr], NULL, compute, (void *)env);
		cthr++;
	}
	cthr = 0;
	while (cthr < CTHR)
	{
		pthread_join(toby[cthr], NULL);
		cthr++;
	}
	return (EXIT_SUCCESS);
}
