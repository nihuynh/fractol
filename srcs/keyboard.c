#include "fractol.h"
#include "libft.h"
#include <stdlib.h>

/*
** Handle keyboard events.
*/

int     deal_keyboard(int key_code, t_env *env)
{
	if (key_code == KEY_SYS_OUT)
		quit_program(env, EXIT_SUCCESS);
	if (DEBUG)
		ft_print_value("\nYou press the key : ", key_code);
	return (0);
}