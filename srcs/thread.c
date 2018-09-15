/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:34:45 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/15 16:25:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void		mt_init(t_env *env)
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
