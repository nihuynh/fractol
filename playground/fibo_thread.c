/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fibo_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 21:30:15 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/03 11:17:00 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Usage : gcc -Wextra -Wall -Werror -lpthread -D_REENTRANT fibo_thread.c && time ./a.out
*/

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

int			ft_fibonacci(int index)
{
	if (index < 0 || index >= 47)
		return (-1);
	if (index == 0)
		return (0);
	if (index == 1 || index == 2)
		return (1);
	return (ft_fibonacci(index - 2) + ft_fibonacci(index - 1));
}

static void* compute(void *i)
{
	printf("\nThe fibonacci of : %i\tas a result of : %i", (int)i, ft_fibonacci((int)i));
	return NULL;
}

int 		main(void)
{
	int thread_count;
	int status;
	pthread_t toby[47];

	thread_count = 0;
	status = 0;
	while (thread_count <= 46)
	{
		status = pthread_create (&toby[thread_count], NULL, compute, (void *) 0 + thread_count);
		thread_count++;
	}
	thread_count = 0;
	while (thread_count <= 46)
	{
		pthread_join(toby[thread_count], NULL);
		thread_count++;
	}
	return (EXIT_SUCCESS);
}
