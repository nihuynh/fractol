/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:32 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/14 03:27:48 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Definition for the fractol project :
** Config :
** TYPE_Z is the type of float use in the complex plane
*/

# define DEBUG 0
# define MAC 0
# define TYPE_Z double
# define ITER_MAX 100
# define THREAD_COUNT 2

/*
** Keybinding :
*/

# define KEY_SYS_OUT 53

/*
** Static def :
*/

# define MACB 1
# define IMAC 2
# define MANDEL 0
# define JULIA 1

/*
** Automatic parameters :
*/

#if (MAC == MACB)
# define WIN_TITLE "Fractol on macbook"
# define VP_WIDTH 1680
# define VP_HEIGHT 1000
# define M_XMIN -2.8
# define M_XMAX 1.3
# define J_X 2
#elif (MAC == IMAC)
# define WIN_TITLE "Fractol @42"
# define VP_WIDTH 2560
# define VP_HEIGHT 1400
# define M_XMIN -2.8
# define M_XMAX 1.3
# define J_X 2.35
#else
# define WIN_TITLE "Fractol"
# define VP_WIDTH 1000
# define VP_HEIGHT 1000
# define M_XMIN -2.1
# define M_XMAX 0.6
# define J_X 2
#endif

/*
** Messages for fractol :
*/

# define MSG_USAGE "\nusage: ./fractol <mandelbrot> <julia>"
# define MSG_BYE "\nQuitting Fractol. Bye bye !"
# define MSG_ERR "\nError cause fractol to exit"

# define USG_ZOOM "Zoom                              ( - E | Q + )"
# define USG_ITER "Iteration                         ( - F | R + )"
# define USG_COLR "Color                         ( shift W | X type )"
# define USG_TYPE "Change fractal                       ( TAB )"
# define USG_ESCP "Toggle mouse / quit             ( SPACE | ESC )"

/*
** Structures :
*/

typedef struct	s_fractal
{
	int			type;
	int			changed;
	TYPE_Z		x1;
	TYPE_Z		x2;
	TYPE_Z		y1;
	TYPE_Z		y2;
	TYPE_Z		step;
	int			iter_max;
	int			rgb;
	int			palette;
	TYPE_Z		c_r;
	TYPE_Z		c_i;
}				t_fractal;

typedef struct	s_pxl
{
	int			iter;
	TYPE_Z		c_r;
	TYPE_Z		c_i;
	TYPE_Z		z_r;
	TYPE_Z		z_i;
	TYPE_Z		square_r;
	TYPE_Z		square_i;
	int			color;
}				t_pxl;

typedef struct	s_slice
{
	TYPE_Z		y1;
	TYPE_Z		y2;
	int			pixel_heigth;
	int			size;
	t_pxl		*data;
}				t_slice;

typedef struct	s_env
{
	t_fractal	d;
	t_slice		s[THREAD_COUNT];
	int			motion_on;
	int			x_mouse;
	int			old_x_mouse;
	int			y_mouse;
	int			old_y_mouse;
	void		*mlx;
	void		*win;
	void		*img;
	int			*imgstr;
	int			b;
	int			w;
	int			e;
}				t_env;

typedef struct	s_pixel
{
	int			iter;
	TYPE_Z		p;
	TYPE_Z		d;
	TYPE_Z		c_r;
	TYPE_Z		c_i;
	TYPE_Z		z_r;
	TYPE_Z		z_i;
	TYPE_Z		square_r;
	TYPE_Z		square_i;
	int			color;
}				t_pixel;


/*
** Prototypes :
*/

int				deal_keyboard(int key_code, t_env *env);
int				deal_mouse(int mouse_code, int x, int y, t_env *env);
int				mouse_motion(int x, int y, t_env *env);

int				render(t_env *env);
void			quit_program(t_env *env, int exit_code);

void			set_mandelbrot(t_fractal *data);
void			set_julia(t_fractal *data);

int				palette(t_fractal fractal, int iter);
void			show_help(void);
void			show_hud(t_env *env, int time_frame);

void			mt_init(t_env *env);

#endif
