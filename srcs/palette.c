/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/11/21 14:17:59 by nihuynh          ###   ########.fr       */
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

static inline TYPE_C	static_pal(int iter, int type, float t)
{
	static TYPE_C color0[16] = { 0x6a2440, 0x19071a, 0x09012f, 0x040449,
		0x000764, 0x0c2c8a, 0x1852b1, 0x397dd1, 0x86b5e5, 0xd3ecf8, 0xf1e9bf,
		0xf8c95f, 0xffaa00, 0xcc8000, 0x995700, 0x6a3403};
	static TYPE_C color1[16] = { 0x421e0f, 0x16176c, 0x4169e1, 0x1e90ff,
		0x00bfff, 0x00f5ff, 0x00ff7f, 0xadff2f, 0xffff00, 0xffa500, 0xff6500,
		0xff3500, 0xff0000, 0xaa0000, 0x880000, 0x580000};
	static TYPE_C color2[64] = { 0xff0005, 0xfe1100, 0xfe2900, 0xfe4100,
	0xfd5800, 0xfd7000, 0xfd8700, 0xfd9f00, 0xfcb600, 0xfcce00, 0xfce500,
	0xfbfb00, 0xe3fb00, 0xcbfb00, 0xb4fb00, 0x9cfa00, 0x85fa00, 0x6dfa00,
	0x56f900, 0x3ff900, 0x27f900, 0x10f900, 0x00f808, 0x00f81f, 0x00f836,
	0x00f74d, 0x00f764, 0x00f77b, 0x00f791, 0x00f6a8, 0x00f6bf, 0x01f6d6,
	0x01f5ec, 0x01e7f5, 0x01d0f5, 0x01b9f5, 0x01a2f4, 0x018cf4, 0x0175f4,
	0x015ef3, 0x0147f3, 0x0131f3, 0x011af3, 0x0104f2, 0x1501f2, 0x2b01f2,
	0x4201f1, 0x5801f1, 0x6e01f1, 0x8501f0, 0x9b01f0, 0xb101f0, 0xc701f0,
	0xdd01ef, 0xef01eb, 0xef01d5, 0xef01bf, 0xee01a8, 0xee0192, 0xee017c,
	0xed0166, 0xed0150, 0xed0139, 0xed0123};

	if (type == 0)
		return (color0[iter % 16]);
	else if (type == 1)
		return (color1[iter % 16]);
	else if (type == 2)
		return ((int)(t * 999997771));
	else
		return (color2[iter % 64]);
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
		else if (ft_btw(env->type_palette, 7, C_PALETTE))
			f->colorp[i] = static_pal(i, env->type_palette - 7, t);
	}
	if (DEBUG)
		ft_putendl("New palette generated");
}
