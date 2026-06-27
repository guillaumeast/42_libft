/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/27 17:42:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

bool	buff_read_until_c(t_buff *const buff, int fd, char c)
{
	ssize_t	read_len;

	read_len = 1;
	while (read_len > 0)
	{
		if (!buff_grow(buff, buff->len + 1))
		{
			read_len = -1;
			break ;
		}
		read_len = buff_read_n_bytes(buff, fd, 1);
		if (read_len > 0 && buff->len > 0 && buff->data[buff->len - 1] == c)
			break ;
	}
	(void)buff_adjust(buff);
	return (read_len >= 0);
}

bool	buff_read_until_n(t_buff *const buff, int fd, size_t n)
{
	ssize_t	read_len;

	if (!buff_grow(buff, buff->len + n))
		return (false);
	read_len = buff_read_n_bytes(buff, fd, n);
	(void)buff_adjust(buff);
	return (read_len >= 0);
}

bool	buff_read_all(t_buff *const buff, int fd)
{
	ssize_t	read_len;

	read_len = 1;
	while (read_len > 0)
	{
		if (!buff_grow(buff, buff->len + 1))
		{
			read_len = -1;
			break ;
		}
		read_len = buff_read_n_bytes(buff, fd, buff->cap - buff->len);
	}
	(void)buff_adjust(buff);
	return (read_len >= 0);
}
