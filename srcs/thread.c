/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:34:45 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/23 03:25:11 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include "fractol.h"
#include "libft.h"

void				mt_init(t_env *env)
{
	int i;

	i = -1;
	env->vp_len = VP_WIDTH * VP_HEIGHT;
	env->s_len = env->vp_len / C_THR;
	while (++i < C_THR)
	{
		env->s[i].id = i;
		env->s[i].env = env;
		if (!(env->s[i].data = ft_memalloc(sizeof(t_pxl) * SLICE_LEN)))
			quit_program(env, EXIT_FAILURE);
	}
}

static inline void	*mt_iter(void *arg)
{
	t_slice	*slice;
	t_env	*env;
	int		i;
	int		ofs;

	slice = arg;
	env = slice->env;
	ofs = slice->id * PXL_HEIGHT;
	i = -1;
	ft_bzero(slice->data, sizeof(t_pxl) * env->s_len);
	while (++i < env->s_len)
		iter_julbrot(env, &slice->data[i], i % VP_WIDTH, ofs + i / VP_WIDTH);
	pthread_exit(NULL);
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
		sats = pthread_create(&toby[cthr], NULL, mt_iter, ptr);
	}
	cthr = -1;
	while (++cthr < C_THR)
		pthread_join(toby[cthr], NULL);
	return (EXIT_SUCCESS);
}
