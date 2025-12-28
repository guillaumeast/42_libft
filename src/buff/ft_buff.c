/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buff.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2025/12/28 13:06:50 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

bool	buff_prepend(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = ft_strlen(str);
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
		strlen = ft_strlen(str);
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
	size_t	new_cap;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		if (!ft_realloc(&b->data, b->cap, new_cap))
			return (false);
		b->cap = new_cap;
	}
	ft_memcpy(b->data + b->len, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_read_all(t_buff *buff, int fd)
{
	ssize_t	read_len;
	char	*final_data;

	read_len = 1;
	while (read_len > 0)
	{
		if (buff->cap - buff->len == 0 && !buff_grow(buff, buff->len + 1))
			return (false);
		read_len = read(fd, buff->data + buff->len, buff->cap - buff->len);
		if (read_len == -1 && errno == EINTR)
			continue ;
		if (read_len > 0)
			buff->len += (size_t)read_len;
	}
	final_data = malloc(buff->len);
	if (final_data)
	{
		ft_memcpy(final_data, buff->data, buff->len);
		free(buff->data);
		buff->data = final_data;
		buff->cap = buff->len;
	}
	return (read_len != -1);
}
