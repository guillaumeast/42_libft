/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:21:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	buff_prepend(t_buff *dst, const t_buff *src)
{
	return (buff_prepend_n(dst, src->data, (long)src->len));
}

bool	buff_insert(t_buff *dst, size_t index, const t_buff *src)
{
	return (buff_insert_n(dst, index, src->data, (long)src->len));
}

bool	buff_append(t_buff *dst, const t_buff *src)
{
	return (buff_append_n(dst, src->data, (long)src->len));
}

bool	buff_dup(t_buff *dst, const t_buff *src)
{
	return (buff_dup_n(dst, src, src->len));
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
