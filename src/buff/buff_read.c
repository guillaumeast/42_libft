/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:24:30 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int	buff_read_until(t_buff *buff, int fd, char c)
{
	ssize_t	read_len;
	int		index;

	index = -1;
	while (index == -1)
	{
		if (buff->cap - buff->len == 0 && !buff_grow(buff, buff->len + 1))
			return (-2);
		read_len = read(fd, buff->data + buff->len, buff->cap - buff->len);
		if (read_len == -1 && errno == EINTR)
			continue ;
		else if (read_len == -1)
			return (-2);
		else if (read_len == 0)
			break ;
		buff->len += (size_t)read_len;
		index = buff_get_index(buff, c);
	}
	buff_adjust(buff);
	return (index);
}

bool	buff_read_all(t_buff *buff, int fd)
{
	ssize_t	read_len;

	while (true)
	{
		if (buff->cap - buff->len == 0 && !buff_grow(buff, buff->len + 1))
			return (false);
		read_len = read(fd, buff->data + buff->len, buff->cap - buff->len);
		if (read_len == -1 && errno == EINTR)
			continue ;
		else if (read_len <= 0)
			break ;
		buff->len += (size_t)read_len;
	}
	buff_adjust(buff);
	return (read_len != -1);
}
