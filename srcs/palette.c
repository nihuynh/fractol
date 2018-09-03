/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/03 23:15:16 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		palette(t_env *env, int iter)
{
	double	t;
	int		rgb;

	if (env->palette == 0)
		return (iter * 255 / env->iter_max << env->rgb);
	t = (double)iter / (double)env->iter_max;
	rgb = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
	rgb += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
	rgb += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return (rgb);
}