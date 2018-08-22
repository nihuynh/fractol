/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:32 by nihuynh           #+#    #+#             */
/*   Updated: 2018/08/23 01:56:32 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Definition for the fractol project :
** Usage and window configuration
*/

# define DEBUG 1

# define WIN_TITLE "Fractol"
# define CURRENT_TITLE "Fractol 0% 23/08 J-7"

# define MSG_USAGE "usage: ./fractol <mandelbrot>"
# define MSG_BYE "Quitting Fractol. Bye bye !"
# define MSG_ERR "Error cause fractol to exit"
# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define KEY_ENABLE 1
# define MOUSE_ENABLE 0
# define KEY_SYS_OUT 53



typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*imgstr;
	int			b;
	int			s;
	int			e;
	double		x1;
	double		x2;
	double		y1;
    double		y2;
	int			zoom;
}				t_env;

void	ft_putpixel(t_env *env, int x, int y, int color);
void	quit_program(t_env *env, int exit_code);
void    ft_new_window(t_env *env, int h, int w, char *title);

#endif
