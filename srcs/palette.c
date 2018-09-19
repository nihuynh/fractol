/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/19 12:58:51 by nihuynh          ###   ########.fr       */
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

static inline int hsv(float h, float s, float v)
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

int     static_palette(int iter)
{
	int colors[16] = {
		0x000000, 0x19071a, 0x09012f, 0x040449, 0x000764, 0x0c2c8a,
        0x1852b1, 0x397dd1, 0x86b5e5, 0xd3ecf8, 0xf1e9bf, 0xf8c95f,
        0xffaa00, 0xcc8000, 0x995700, 0x6a3403
    };

    return (colors[iter % 16]);
}

/*
** Choose the color for the pixel depending on the iteration & max iteration.
*/

inline void	palalloc(t_env *env, t_fractal *f)
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
			f->colorp[i] = static_palette(i);
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
	ft_putendl(USG_ESCP);
	return (1);
}
