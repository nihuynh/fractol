/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/26 15:09:22 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

static inline TYPE_C	rgbtoi(float r, float g, float b)
{
	TYPE_C	res;

	res = (int)(r * 255) << 16;
	res += (int)(g * 255) << 8;
	res += (int)(b * 255);
	return (res);
}

static inline TYPE_C	bernstein(t_env *env, float t)
{
	float r;
	float g;
	float b;

	r = 9 * (1 - t) * t * t * t;
	g = 15 * (1 - t) * (1 - t) * t * t;
	b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t;
	if (env->type_palette == 1)
		return (rgbtoi(r, b, g));
	else if (env->type_palette == 2)
		return (rgbtoi(b, g, r));
	else if (env->type_palette == 3)
		return (rgbtoi(b, r, g));
	else if (env->type_palette == 4)
		return (rgbtoi(g, b, r));
	else if (env->type_palette == 5)
		return (rgbtoi(g, r, b));
	return (rgbtoi(r, g, b));
}

static inline TYPE_C	hsv(float h, float s, float v)
{
	int		ti;
	float	f;
	float	l;
	float	m;
	float	n;

	h *= 360;
	ti = (int)((int)(h / 60.0) % 6);
	f = h / 60 - ti;
	l = v * (1 - s);
	m = v * (1 - f * s);
	n = v * (1 - (1 - f) * s);
	if (ti == 0)
		return (rgbtoi(v, n, l));
	else if (ti == 1)
		return (rgbtoi(m, v, l));
	else if (ti == 2)
		return (rgbtoi(l, v, n));
	else if (ti == 3)
		return (rgbtoi(l, m, v));
	else if (ti == 4)
		return (rgbtoi(n, l, v));
	else if (ti == 5)
		return (rgbtoi(v, l, m));
	return (rgbtoi(0, 0, 0));
}

static inline TYPE_C	static_small(int iter)
{
	static TYPE_C colors[16] = { 0x000000, 0x19071a, 0x09012f, 0x040449,
		0x000764, 0x0c2c8a, 0x1852b1, 0x397dd1, 0x86b5e5, 0xd3ecf8, 0xf1e9bf,
		0xf8c95f, 0xffaa00, 0xcc8000, 0x995700, 0x6a3403};

	return (colors[iter % 16]);
}

/*
** Choose the color for the pixel depending on the iteration & max iteration.
*/

void					palalloc(t_env *env, t_fractal *f)
{
	float	t;
	int		i;

	i = -1;
	env->d.new_pal = 0;
	if (f->colorp != NULL)
		free(f->colorp);
	if (!(f->colorp = ft_memalloc(f->iter_max * sizeof(int))))
		quit_program(env, EXIT_FAILURE);
	while (++i < f->iter_max)
	{
		t = (float)i / (float)f->iter_max;
		if (ft_btw(env->type_palette, 0, 5))
			f->colorp[i] = bernstein(env, t);
		else if (env->type_palette == 6)
			f->colorp[i] = hsv(t, 1, 0.7);
		else if (env->type_palette == 7)
			f->colorp[i] = static_small(i);
	}
	if (DEBUG)
		ft_putendl("New palette generated");
}
