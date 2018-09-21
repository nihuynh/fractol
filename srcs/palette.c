/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/21 03:35:05 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

int	rgbtoi(float r, float g, float b)
{
	int res;

	res = (int)(r * 255) << 16;
	res += (int)(g * 255) << 8;
	res += (int)(b * 255);
	return (res);
}

static inline int bernstein(t_env *env, float t)
{
	float r;
	float g;
	float b;

	r = 9 * (1 - t) * t * t * t;
	g = 15 * (1 - t) * (1 - t) * t * t;
	b = 8.5 * (1 - t) * (1 - t) * (1 - t) * t;
	if (env->cshift == 1)
		return (rgbtoi(r, b, g));
	else if (env->cshift == 2)
		return (rgbtoi(b, g, r));
	else if (env->cshift == 3)
		return (rgbtoi(b, r, g));
	else if (env->cshift == 4)
		return (rgbtoi(g, b, r));
	else if (env->cshift == 5)
		return (rgbtoi(g, r, b));
	return (rgbtoi(r, g, b));
}

static inline int	hsv(float h, float s, float v)
{
	float c;
	float x;
	int hh;

	h *= 360;
	c = v * s;
	hh = (int)(h / 60.0);
	x = c * (1 - ft_abs(hh % 2 - 1));
	if (hh == 0)
		return (rgbtoi(c, x, 0));
	else if (hh == 1)
		return (rgbtoi(x, c, 0));
	else if (hh == 2)
		return (rgbtoi(0, c, x));
	else if (hh == 3)
		return (rgbtoi(0, x, c));
	else if (hh == 4)
		return (rgbtoi(x, 0, c));
	else if (hh == 5)
		return (rgbtoi(c, 0, x));
	return (rgbtoi(0, 0, 0));
}

static inline int	static_small(int iter)
{
	int colors[16] = {
		0x000000, 0x19071a, 0x09012f, 0x040449, 0x000764, 0x0c2c8a,
        0x1852b1, 0x397dd1, 0x86b5e5, 0xd3ecf8, 0xf1e9bf, 0xf8c95f,
        0xffaa00, 0xcc8000, 0x995700, 0x6a3403
    };

    return (colors[iter % 16]);
}

static inline int	static_big(int iter)
{
    int colors[] = {
    0xf7df, 0xff5a, 0x07ff, 0x7ffa, 0xf7ff, 0xf7bb, 0xff38, 0xff59, 0x001f,
	0x895c, 0xa145, 0xddd0, 0x5cf4, 0x7fe0, 0xd343, 0xfbea, 0x64bd, 0xffdb,
	0xd8a7,	0x07ff, 0x0011, 0x0451, 0xbc21, 0xad55, 0x0320, 0xbdad, 0x8811,
	0x5345, 0xfc60,	0x9999, 0x8800, 0xecaf, 0x8df1, 0x49f1, 0x2a69, 0x067a,
	0x901a, 0xf8b2, 0x05ff,	0x6b4d, 0x1c9f, 0xd48e, 0xb104, 0xffde, 0x2444,
	0xf81f, 0xdefb, 0xffdf, 0xfea0,	0xdd24, 0x8410, 0x0400, 0xafe5, 0xf7fe,
	0xfb56, 0xcaeb, 0x4810, 0xfffe, 0xf731,	0xe73f, 0xff9e, 0x7fe0, 0xffd9,
	0xaedc, 0xf410, 0xe7ff, 0xffda, 0xd69a, 0x9772,	0xfdb8, 0xfd0f, 0x2595,
	0x867f, 0x839f, 0x7453, 0xb63b, 0xfffc, 0x07e0, 0x3666,	0xff9c, 0xf81f,
	0x8000, 0x6675, 0x0019, 0xbaba, 0x939b, 0x3d8e, 0x7b5d, 0x07d3,	0x4e99,
	0xc0b0, 0x18ce, 0xf7ff, 0xff3c, 0xff36, 0xfef5, 0x0010, 0xffbc, 0x8400,
	0x6c64, 0xfd20, 0xfa20, 0xdb9a, 0xef55, 0x9fd3, 0xaf7d, 0xdb92, 0xff7a,
	0xfed7,	0xcc27, 0xfe19, 0xdd1b, 0xb71c, 0x8010, 0xf800, 0xbc71, 0x435c,
	0x8a22, 0xfc0e,	0xf52c, 0x2c4a, 0xffbd, 0xa285, 0xc618, 0x867d, 0x6ad9,
	0x7412, 0xffdf, 0x07ef,	0x4416, 0xd5b1, 0x0410, 0xddfb, 0xfb08, 0x471a,
	0xec1d, 0xd112, 0xf6f6, 0xffff,	0xf7be, 0xffe0, 0x9e66, 0x0000
	};

    return (colors[iter % 142]);
}

/*
** Choose the color for the pixel depending on the iteration & max iteration.
*/

void				palalloc(t_env *env, t_fractal *f)
{
	float	t;
	int		i;

	i = -1;
	if (f->colorp != NULL)
		free(f->colorp);
	if (!(f->colorp = ft_memalloc(f->iter_max * sizeof(int))))
		quit_program(env, EXIT_FAILURE);
	while (++i < f->iter_max)
	{
		t = (float)i / (float)f->iter_max;
		if (env->ctype == 0)
			f->colorp[i] = bernstein(env, t);
		else if (env->ctype == 1)
			f->colorp[i] = hsv(t, 1, 1);
		else if (env->ctype == 2)
			f->colorp[i] = static_small(i);
		else if (env->ctype == 3)
			f->colorp[i] = static_big(i);
	}
}

/*
** Print the command on the terminal when the key H is press.
*/

inline int	show_help(void)
{
	ft_putendl("\n\n\n\n\n\n\n\n\n");
	ft_putendl(USG_TYPE);
	ft_putendl(USG_ZOOM);
	ft_putendl(USG_ITER);
	ft_putendl(USG_COLOR);
	ft_putendl(USG_ESCP);
	return (1);
}
