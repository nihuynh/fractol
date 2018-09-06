/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:32 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/06 16:20:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Definition for the fractol project :
** Usage and window configuration
*/

# define DEBUG 1
# define MAC MACBOOK


# define MACBOOK 0
# define IMAC 1

#if (MAC == MACBOOK)
# define WIN_TITLE "Fractol on macbook"
# define VP_WIDTH 1680
# define VP_HEIGHT 1000
# define M_XMIN -2.8
# define M_XMAX 1.3
# define J_X 1.8
#elif (MAC == IMAC)
# define WIN_TITLE "Fractol @42"
# define VP_WIDTH 2560
# define VP_HEIGHT 1400
# define M_XMIN -2.8
# define M_XMAX 1.3
# define J_X 2.35
#else
# define WIN_TITLE "Fractol"
# define VP_WIDTH 600
# define VP_HEIGHT 600
# define M_XMIN -2.1
# define M_XMAX 0.6
# define J_X 1.2
#endif

# define CURRENT_TITLE "Fractol 0% 23/08 J-7"

# define MSG_USAGE "\nusage: ./fractol <mandelbrot>"
# define MSG_BYE "\nQuitting Fractol. Bye bye !"
# define MSG_ERR "\nError cause fractol to exit"
# define KEY_ENABLE 1
# define MOUSE_ENABLE 1
# define KEY_SYS_OUT 53

# define ITER_MAX 100
# define MANDEL 0
# define JULIA 1

typedef struct	s_env
{
	int			type;
	int			motion_on;
	double		x1;
	double		old_x1;
	double		x2;
	double		old_x2;
	double		y1;
	double		old_y1;
	double		y2;
	double		old_y2;
	int			iter_max;
	int			old_iter_max;
	double		step_x;
	double		step_y;
	int			x_mouse;
	int			old_x_mouse;
	int			y_mouse;
	int			old_y_mouse;
	int			rgb;
	int			old_rgb;
	int			palette;
	int			old_palette;
	double		c_r;
	double		old_c_r;
	double		c_i;
	double		old_c_i;
	int			win_w;
	int			win_h;
	void		*mlx;
	void		*win;
	void		*img;
	int			*imgstr;
	int			b;
	int			s;
	int			e;
}				t_env;

int				deal_keyboard(int key_code, t_env *env);
void			zoom(t_env *env, double value);

int				deal_mouse(int mouse_code, int x, int y, t_env *env);
int				mouse_motion(int x, int y, t_env *env);

int				render(t_env *env);
void			quit_program(t_env *env, int exit_code);

void			set_mandelbrot(t_env *env);
void			set_julia(t_env *env);

int				palette(t_env *env, int iter);
void			show_help(void);

#endif
