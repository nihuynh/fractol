/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/03 22:57:20 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/15 15:34:30 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "libft.h"
#include "mlx.h"
#include <stdlib.h>

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
		f->colorp[i] = ((int)(9 * (1 - t) * t * t * t * 255) << 16);
		f->colorp[i] += ((int)(15 * (1 - t) * (1 - t) * t * t * 255) << 8);
		f->colorp[i] += (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
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
