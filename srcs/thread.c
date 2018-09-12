/* ************************************************************************** */

# include <pthread.h>
#include "fractol.h"
#include "libft.h"
#include <stdlib.h>


void		mt_init(t_env *env)
{
    int i;

    i = -1;
    while(++i < THREAD_COUNT)
    {
        env->s[i].pixel_heigth = VP_HEIGHT / THREAD_COUNT;
        env->s[i].size = VP_WIDTH * env->s[i].pixel_heigth;
        if (!(env->s[i].data = ft_memalloc(sizeof(t_pxl) * env->s[i].size)))
            quit_program(env, EXIT_FAILURE);
    }
}

static inline void* mj_fct(void *data)
{
	
	return (NULL);
}

/*
** Render one frame when the env has changed.
*/

inline void	mt_render(t_env *env)
{
	clock_t start;
	clock_t time_frame;
	int status;
	int i;
	pthread_t toby[THREAD_COUNT];

	if (env->d.changed)
	{
		i = -1;
		status = 0;
		start = clock();
		env->d.changed = 0;
		while (++i <= THREAD_COUNT && !status)
			status = pthread_create(&toby[i], NULL, mj_fct, (void *)&env->s[i]);
		i = -1;
		while (++i <= THREAD_COUNT)
			pthread_join(toby[i], NULL);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		time_frame = clock() - start;
		show_hud(env, (int) time_frame/1000);
	}
}