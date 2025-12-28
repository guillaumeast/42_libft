/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:37 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/28 12:57:26 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#define DEFAULT_BUFF_CAP 128
#define BUFF_GROWTH 2

bool	buff_init(t_buff *b, size_t initial_cap)
{
	b->cap = 0;
	if (initial_cap > 0)
	{
		b->data = malloc(initial_cap);
		if (!b->data)
			return (false);
	}
	else
		b->data = NULL;
	b->cap = initial_cap;
	b->len = 0;
	return (true);
}

size_t	buff_get_required_cap(size_t current_cap, size_t target_len)
{
	size_t	new_cap;

	if (target_len == 0)
		return (current_cap);
	if (current_cap == 0)
		new_cap = DEFAULT_BUFF_CAP;
	else
		new_cap = current_cap;
	while (new_cap <= target_len)
		new_cap *= BUFF_GROWTH;
	return (new_cap);
}

bool	buff_grow(t_buff *buff, size_t target_len)
{
	size_t	new_cap;
	char	*new_data;
	
	new_cap = buff_get_required_cap(buff->cap, target_len);
	if (new_cap == buff->cap)
		return (true);
	new_data = malloc(new_cap);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = new_cap;
	return (true);
}

void	buff_free(t_buff *b)
{
	if (b->data)
		free(b->data);
	b->data = NULL;
}
