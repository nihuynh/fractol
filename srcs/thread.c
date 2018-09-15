/* ************************************************************************** */

# include <pthread.h>
#include "fractol.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

void		mt_init(t_env *env)
{
    int i;

    i = -1;
    while(++i < THREAD_COUNT)
    {
		env->s[i].y1 = env->d.y1 + i * env->d.step * PXL_HEIGHT;
		env->s[i].y2 = env->d.y1 + (i + 1) * env->d.step * PXL_HEIGHT;
        printf("\nSlice %i btw %f / %f.", i, env->s[i].y1, env->s[i].y2);
        ft_putchar('+');
        if (!(env->s[i].data = ft_memalloc(sizeof(t_pxl) * SLICE_LEN)))
            quit_program(env, EXIT_FAILURE);
    }
    printf("the i is %i", i);
}
