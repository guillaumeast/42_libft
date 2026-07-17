/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_ops_vectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:41:15 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/17 15:59:20 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

static bool	grow_and_merge(t_vector *dst, const t_vector *src, size_t index);
static bool	compute_new_cap(size_t dst_len, size_t src_len, size_t *new_cap);

bool	vector_merge(t_vector *dst, const t_vector *src, size_t index)
{
	size_t	target_len;

	if (dst == src)
		return (false);
	if (index > dst->len)
		return (false);
	if (dst->item_size != src->item_size)
		return (false);
	if (dst->len > SIZE_MAX - src->len)
		return (false);
	target_len = dst->len + src->len;
	if (dst->cap < target_len)
		return (grow_and_merge(dst, src, index));
	ft_memmove(
		dst->data + ((index + src->len) * dst->item_size),
		dst->data + (index * dst->item_size),
		(dst->len - index) * dst->item_size);
	ft_memcpy(
		dst->data + (index * dst->item_size),
		src->data,
		src->len * src->item_size);
	dst->len = target_len;
	return (true);
}

void	vector_clear(t_vector *vector, void (*del)(void *))
{
	size_t	i;

	if (del != NULL)
	{
		i = 0;
		while (i < vector->len)
		{
			del((char *)vector->data + (i * vector->item_size));
			i++;
		}
	}
	vector->len = 0;
}

static bool	grow_and_merge(t_vector *dst, const t_vector *src, size_t index)
{
	size_t	newcap;
	size_t	old_cap;
	void	*newdata;

	newcap = dst->cap;
	if (newcap == 0)
		newcap = VECTOR_INIT_CAP;
	if (!compute_new_cap(dst->len, src->len, &newcap)
		|| newcap > SIZE_MAX / dst->item_size)
		return (false);
	newdata = malloc(newcap * dst->item_size);
	if (!newdata)
		return (false);
	old_cap = dst->cap;
	ft_memcpy(newdata, dst->data, index * dst->item_size);
	ft_memcpy(
		newdata + ((index + src->len) * dst->item_size),
		dst->data + (index * dst->item_size),
		(dst->len - index) * dst->item_size);
	ft_memcpy(
		newdata + (index * dst->item_size), src->data,
		src->len * dst->item_size);
	if (old_cap > 0)
		free(dst->data);
	return (dst->data = newdata, dst->cap = newcap, dst->len += src->len, true);
}

static bool	compute_new_cap(size_t dst_len, size_t src_len, size_t *new_cap)
{
	size_t	target_len;
	size_t	tmp_new_cap;

	if (dst_len > SIZE_MAX - src_len)
		return (false);
	target_len = dst_len + src_len;
	if (!new_cap || *new_cap > SIZE_MAX / 2)
		return (false);
	tmp_new_cap = *new_cap;
	while (tmp_new_cap < target_len)
	{
		if (tmp_new_cap > SIZE_MAX / 2)
			return (false);
		tmp_new_cap *= 2;
	}
	*new_cap = tmp_new_cap;
	return (true);
}

void	vector_take(t_vector *dst, t_vector *src)
{
	*dst = *src;
	src->cap = 0;
}
