/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:32:37 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	string_prepend(t_string *dst, const t_string *src)
{
	return (string_prepend_n(dst, src->data, (long)src->len));
}

bool	string_insert(
	t_string *const dst,
	size_t index,
	const t_string *const src)
{
	return (string_insert_n(dst, index, src->data, (long)src->len));
}

bool	string_append(t_string *dst, const t_string *src)
{
	return (string_append_n(dst, src->data, (long)src->len));
}

bool	string_dup(t_string *dst, const t_string *src)
{
	return (string_dup_n(dst, src, src->len));
}

void	string_rm_part(t_string *string, size_t i_start, ssize_t len)
{
	char	*dst;
	char	*src;
	size_t	len_to_move;

	if (i_start >= string->len)
		return ;
	else if (len < 0 || i_start + (size_t)len > string->len)
	{
		string->len = i_start;
		string->data[string->len] = '\0';
		return ;
	}
	dst = string->data + i_start;
	src = string->data + i_start + (size_t)len;
	len_to_move = string->len - (i_start + (size_t)len);
	ft_memmove(dst, src, len_to_move);
	string->len -= (size_t)len;
	string->data[string->len] = '\0';
}
