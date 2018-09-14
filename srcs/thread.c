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
        if (!(env->s[i].data = ft_memalloc(sizeof(t_pxl) * SLICE_LEN)))
            quit_program(env, EXIT_FAILURE);
		env->s[i].id = i;
		env->s[i].env = &env;
		env->s[i].fractal = &env->fractal;
    }
}

static inline void* mj_fct(void *data)
{
	int i;
	t_slice *slice;

	i = -1;
	slice = (t_slice)data;
	while (++i < SLICE_LEN)
	{
		
	}

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
		status ^= status;
		start = clock();
		env->d.changed = 0;
		if (!env->colorp)
			free(env->colorp);
		env->colorp = palalloc(env->d.iter_max);
		while (++i <= THREAD_COUNT && !status)
			status = pthread_create(&toby[i], NULL, mj_fct, (void *)&env->s[i].data);
		i = -1;
		while (++i <= THREAD_COUNT)
			pthread_join(toby[i], NULL);
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
		time_frame = clock() - start;
		show_hud(env, (int) time_frame/1000);
	}
}