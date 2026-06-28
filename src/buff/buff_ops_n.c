/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_ops_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:20:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <stdlib.h>

bool	buff_prepend_n(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	if (strlen == 0)
		return (true);
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		b->cap = new_cap;
		ft_memcpy(new_data + strlen, b->data, b->len);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + strlen, b->data, b->len);
	ft_memcpy(b->data, str, strlen);
	return (b->len = b->len + strlen, true);
}

bool	buff_insert_n(t_buff *b, size_t index, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	strlen = (size_t)n;
	if (n < 0)
		strlen = str_len(str);
	if (strlen == 0)
		return (true);
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		b->cap = new_cap;
		ft_memcpy(new_data, b->data, index);
		ft_memcpy(new_data + index + strlen, b->data + index, b->len - index);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + index + strlen, b->data + index, b->len - index);
	ft_memcpy(b->data + index, str, strlen);
	return (b->len = b->len + strlen, true);
}

bool	buff_append_n(t_buff *b, const char *str, long n)
{
	size_t	strlen;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	if (strlen == 0)
		return (true);
	if (!buff_grow(b, b->len + strlen))
		return (false);
	ft_memcpy(b->data + b->len, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_dup_n(t_buff *dst, const t_buff *src, size_t n)
{
	if (n > src->len)
		n = src->len;
	dst->len = 0;
	if (!buff_append_n(dst, src->data, (long)n))
	{
		buff_free(dst);
		return (false);
	}
	return (true);
}
