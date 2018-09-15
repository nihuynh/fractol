/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fibo_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 21:30:15 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/15 16:42:01 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Usage : gcc -Wextra -Wall -Werror -pthread fibo_thread.c && time ./a.out
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static inline int	ft_fibonacci(int index)
{
	if (index < 0 || index >= 47)
		return (-1);
	if (index == 0)
		return (0);
	if (index == 1 || index == 2)
		return (1);
	return (ft_fibonacci(index - 2) + ft_fibonacci(index - 1));
}

static inline void	*compute(void *i)
{
	printf("\nThe fibonacci of : %i\tas a result of : %i", \
			(int)i, ft_fibonacci((int)i));
	return (NULL);
}

int					main(void)
{
	intptr_t	cthr;
	int			status;
	pthread_t	toby[47];

	cthr = 0;
	status = 0;
	while (cthr <= 46 && !status)
	{
		status = pthread_create(&toby[cthr], NULL, compute, (void *)cthr);
		cthr++;
	}
	cthr = 0;
	while (cthr <= 46)
	{
		pthread_join(toby[cthr], NULL);
		cthr++;
	}
	return (EXIT_SUCCESS);
}
