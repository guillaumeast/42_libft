/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/14 03:27:51 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <stdlib.h>

bool	buff_prepend(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
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
	b->len = b->len + strlen;
	return (true);
}

bool	buff_insert(t_buff *b, size_t index, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
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
	b->len = b->len + strlen;
	return (true);
}

bool	buff_append(t_buff *b, const char *str, long n)
{
	size_t	strlen;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	if (!buff_grow(b, b->len + strlen))
		return (false);
	ft_memcpy(b->data + b->len, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

t_buff	*buff_dup_n(const t_buff *src, size_t n)
{
	t_buff	*res;

	res = malloc(sizeof * res);
	if (!res)
		return (NULL);
	if (n > src->len)
		n = src->len;
	buff_init(res, 0);
	if (!buff_append(res, src->data, (long)n))
	{
		buff_free(res);
		free(res);
		return (NULL);
	}
	return (res);
}

void	buff_rm_part(t_buff *buff, size_t i_start, ssize_t len)
{
	char	*dst;
	char	*src;
	size_t	len_to_move;

	if (i_start >= buff->len)
		return ;
	else if (len < 0 || i_start + (size_t)len > buff->len)
	{
		buff->len = i_start;
		return ;
	}
	dst = buff->data + i_start;
	src = buff->data + i_start + (size_t)len;
	len_to_move = buff->len - (i_start + (size_t)len);
	ft_memmove(dst, src, len_to_move);
	buff->len -= (size_t)len;
}
