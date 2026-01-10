/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:20:10 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief Reads from a file descriptor until a specific character is found.
 *
 * @param buff Pointer to the buffer.
 * @param fd File descriptor to read from.
 * @param c Character to search for.
 * @return Index of c (>= 0), -1 if c not found (EOF), -2 on read error.
 */
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

/**
 * @brief Reads all available data from a file descriptor into buffer.
 *
 * @note On failure, buff->data is not automatically freed.
 *
 * @param buff Pointer to the buffer.
 * @param fd File descriptor to read from.
 * @return true on success, false if read failed.
 */
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
