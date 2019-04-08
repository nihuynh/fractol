/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   livetime.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 02:30:46 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 22:21:29 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include "livetime.h"

void	ft_memdel(void **ap)
{
	if (ap)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	*lt_add(t_lt **lt, void *data, void destruct(void *), int mode)
{
	t_lt *node;

	if (data != NULL)
	{
		if (!(node = (t_lt*)malloc(sizeof(t_lt))))
			return (NULL);
		node->next = *lt;
		node->destruct = destruct;
		node->data = data;
		*lt = node;
		return (data);
	}
	lt_destroy(lt);
	if (mode == EXIT_ONFAIL)
		exit(1);
	return (NULL);
}

t_lt	*lt_get(t_lt *lt, t_lt **prev_lt, void *data)
{
	while (lt != NULL && lt->data != data)
	{
		*prev_lt = lt;
		lt = lt->next;
	}
	return (lt);
}

int		lt_detach(t_lt **lt, void *data)
{
	t_lt *prev_lt;
	t_lt *wanted_lt;

	prev_lt = NULL;
	if (!(wanted_lt = lt_get(*lt, &prev_lt, data)))
		return (1);
	if (prev_lt != NULL)
		prev_lt->next = wanted_lt->next;
	else
		*lt = wanted_lt->next;
	ft_memdel((void **)&wanted_lt);
	return (0);
}

int		lt_destroy(t_lt **lt)
{
	t_lt *next_lt;

	if (!(*lt))
		return (1);
	while (*lt != NULL)
	{
		(*lt)->destruct((*lt)->data);
		(*lt)->data = NULL;
		next_lt = (*lt)->next;
		(*lt)->next = NULL;
		ft_memdel((void **)lt);
		*lt = next_lt;
	}
	return (0);
}
