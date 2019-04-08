/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   livetime.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihuynh <nihuynh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 00:25:07 by nihuynh           #+#    #+#             */
/*   Updated: 2019/04/08 22:23:28 by nihuynh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIVETIME_H
# define LIVETIME_H

# define EXIT_ONFAIL 3

typedef struct s_lt	t_lt;

struct				s_lt
{
	void			*data;
	void			(*destruct)(void *);
	t_lt			*next;
};

void				*lt_add(t_lt **lt, void *data, void rm(void *), int mode);
int					lt_detach(t_lt **lt, void *data);
int					lt_destroy(t_lt **lt);

#endif
