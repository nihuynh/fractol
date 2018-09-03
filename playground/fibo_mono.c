/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fibo_mono.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 21:30:15 by nihuynh           #+#    #+#             */
/*   Updated: 2018/09/02 22:46:50 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>

/*
** Usage : gcc -Wextra -Wall -Werror fibo_mono.c && time ./a.out
*/

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

void compute(int i)
{
	printf("\nThe fibonacci of : %i\tas a result of : %i", i, ft_fibonacci(i));
}

int 		main(void)
{
	int index;

	index = 0;
	while (index < 47)
	{
		compute(index);
		index++;
	}
	return (0);
}
