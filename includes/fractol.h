/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 01:56:32 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 22:41:54 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

/*
** Definition for the fractol project :
** Config :
** TYPE_Z is the type of float use in the complex plane
*/

# define DEBUG		0
# define DEBUG_LEAK	0
# define MAC		IMAC
# define TYPE_Z		double
# define Z_ABS(x)	fabs(x)
# define ITER_MAX	100
# define C_THR		8
# define DTOA_DSCP	7
# define INVERSE_M	1
# define C_PALETTE	10
# define C_UI		16777215

/*
** Keybinding :
*/

# define KEY_SYS_OUT 53

/*
** Static def :
** TYPE_C is the type for the imgstr
** C_UI is the default color for the text
*/

# define DEV			0
# define MACB			1
# define IMAC			2
# define IMAC4K			3
# define MANDEL			0
# define JULIA			1
# define BURNING		2
# define BURNING_JULIA	3
# define SYM			4
# define SYM_JULIA		5
# define TYPE_C			unsigned int

# define EXIT_FAILURE	1
# define EXIT_SUCCESS	0

/*
** Automatic parameters :
*/

# if (MAC == MACB)
#  define WIN_TITLE		"Fractol on macbook"
#  define VP_WIDTH		1680
#  define VP_HEIGHT		1000
#  define M_XMIN		-2.8
#  define M_XMAX		1.3
#  define J_X			2
#  define BJ_X			3
# elif (MAC == IMAC)
#  define WIN_TITLE		"Fractol @42"
#  define VP_WIDTH		2560
#  define VP_HEIGHT		1400
#  define M_XMIN		-2.8
#  define M_XMAX		1.3
#  define J_X			2.35
#  define BJ_X			3
# elif (MAC == IMAC4K)
#  define WIN_TITLE		"Fractol @42"
#  define VP_WIDTH		3200
#  define VP_HEIGHT		1800
#  define M_XMIN		-2.8
#  define M_XMAX		1.3
#  define J_X			2.35
#  define BJ_X			3
# else
#  define WIN_TITLE		"Fractol"
#  define VP_WIDTH		1000
#  define VP_HEIGHT		1000
#  define M_XMIN		-2.1
#  define M_XMAX		0.6
#  define J_X			2
#  define BJ_X			2
# endif

# define B_X			2
# define B_X_OFS		0.5
# define B_Y_OFS		0.5

/*
** Messages for fractol :
*/

# define MSG_USAGE	"usage: ./fractol <mandelbrot> <julia> <burning> <burnlia>"
# define MSG_BYE	"Quitting Fractol. Bye bye !"
# define MSG_ERR	"Error cause fractol to exit"

# define CMD_1		"1 | 2 | 3 | 4 | 5 | 6 => select fractal"
# define CMD_2		" P | scroll => Color | Zoom"
# define CMD_3		" Arrow | Esc    => Move  | Quit"
# define CMD_4		"  R or T + (50) | - F or G (1)   => Iteration"
# define CMD_5		"Space lock or unlock the mouse"
# define CMD_6		"  Q + | - E    => Zoom"
# define CMD_7		"Click will load the parameter into the next fractal"

# define CMD_10		"  Q + | - E    => Zoom"

# define UHELP		"H toggle HUD | C show controls"

/*
** Structures :
*/

typedef struct	s_fractal
{
	int			type;
	int			changed;
	int			reiter;
	int			new_pal;
	TYPE_C		*colorp;
	TYPE_Z		x1;
	TYPE_Z		x2;
	TYPE_Z		y1;
	TYPE_Z		y2;
	TYPE_Z		step;
	int			iter_max;
	TYPE_Z		c_r;
	TYPE_Z		c_i;
}				t_fractal;

typedef struct	s_pxl
{
	int			iter;
}				t_pxl;

typedef struct	s_pixel
{
	TYPE_Z		z_r;
	TYPE_Z		z_i;
	TYPE_Z		c_r;
	TYPE_Z		c_i;
	TYPE_Z		square_r;
	TYPE_Z		square_i;
}				t_pixel;

typedef struct	s_slice
{
	int			id;
	t_pxl		*data;
	void		*env;
}				t_slice;

typedef struct	s_env
{
	t_fractal	d;
	t_slice		s[C_THR];
	int			vp_len;
	int			s_len;
	int			type_palette;
	int			motion_on;
	int			hud_on;
	int			hud_cmd;
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

/*
** Prototypes :
*/

int				deal_keyboard(int key_code, t_env *env);
int				deal_mouse(int mouse_code, int x, int y, t_env *env);
int				mouse_motion(int x, int y, t_env *env);

int				render(t_env *env);
void			quit_program(t_env *env, int exit_code);

void			set_mandelbrot(t_fractal *data);
void			set_julia(t_fractal *data, int type);
void			set_burning(t_fractal *data);
void			set_sym(t_fractal *data);

void			palalloc(t_env *env, t_fractal *f);
int				show_help(void);
void			show_hud(t_env *env, int time_frame);

void			mt_init(t_env *env);
int				mt_render(t_env *env);
void			iter_julbrot(t_env *env, t_pxl *pxl, int x, int y);
void			reiter_julbrot(t_env *env, t_pxl *pxl, int x, int y);

#endif
