/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:20:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	buff_init(t_buff *buff, size_t initial_cap, const char *str, long n)
{
	buff->data = NULL;
	buff->cap = 0;
	buff->len = 0;
	if (initial_cap > 0)
	{
		buff->data = malloc(initial_cap);
		if (!buff->data)
			return (false);
		buff->cap = initial_cap;
	}
	if (str)
		return (buff_append_n(buff, str, n));
	return (true);
}

void	buff_free(t_buff *buff)
{
	if (buff->data)
		free(buff->data);
	buff->len = 0;
	buff->cap = 0;
	buff->data = NULL;
}

void	buff_free_void(void *buff)
{
	buff_free(buff);
}
