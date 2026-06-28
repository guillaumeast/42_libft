/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_life_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:41:21 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:41:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

bool	vector_init(t_vector *vector, size_t item_size, size_t cap)
{
	vector->data = NULL;
	vector->cap = 0;
	vector->len = 0;
	vector->item_size = item_size;
	if (item_size == 0)
		return (false);
	if (cap == 0)
		return (true);
	if (cap > SIZE_MAX / item_size)
		return (false);
	vector->data = malloc(cap * item_size);
	if (!vector->data)
		return (false);
	vector->cap = cap;
	return (true);
}

bool	vector_grow(t_vector *vector)
{
	size_t	new_cap;
	void	*new_data;

	if (vector->cap > SIZE_MAX / 2)
		return (false);
	new_cap = vector->cap * 2;
	if (new_cap == 0)
		new_cap = VECTOR_INIT_CAP;
	if (new_cap > SIZE_MAX / vector->item_size)
		return (false);
	new_data = malloc(new_cap * vector->item_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, vector->data, vector->len * vector->item_size);
	free(vector->data);
	vector->data = new_data;
	vector->cap = new_cap;
	return (true);
}

bool	vector_adjust(t_vector *vector)
{
	void	*new_data;

	if (vector->len == 0)
	{
		vector_free(vector, NULL);
		return (true);
	}
	if (vector->cap == vector->len)
		return (true);
	new_data = malloc(vector->len * vector->item_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, vector->data, vector->len * vector->item_size);
	free(vector->data);
	vector->data = new_data;
	vector->cap = vector->len;
	return (true);
}

bool	vector_dup(t_vector *dst, t_vector *src)
{
	if (dst == src)
		return (false);
	if (!vector_init(dst, src->item_size, src->cap))
		return (false);
	if (!vector_merge(dst, src, 0))
	{
		vector_free(dst, NULL);
		return (false);
	}
	return (true);
}

void	vector_free(t_vector *vector, void (*item_free)(void *item))
{
	size_t	i;
	char	*data;

	if (item_free)
	{
		data = (char *)vector->data;
		i = 0;
		while (i < vector->len)
		{
			item_free(data + (i * vector->item_size));
			i++;
		}
	}
	free(vector->data);
	vector->data = NULL;
	vector->len = 0;
	vector->cap = 0;
}
