/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_internal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 14:13:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/27 17:01:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_BUFF_CAP	128
#define BUFF_GROWTH			2

size_t	buff_get_required_cap(size_t current_cap, size_t target_len)
{
	size_t	new_cap;

	if (target_len == 0)
		return (current_cap);
	if (current_cap == 0)
		new_cap = DEFAULT_BUFF_CAP;
	else
		new_cap = current_cap;
	while (new_cap <= target_len)
		new_cap *= BUFF_GROWTH;
	return (new_cap);
}

bool	buff_grow(t_buff *const buff, size_t target_len)
{
	size_t	new_cap;
	char	*new_data;

	new_cap = buff_get_required_cap(buff->cap, target_len);
	if (new_cap == buff->cap)
		return (true);
	new_data = malloc(new_cap);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = new_cap;
	return (true);
}

ssize_t	buff_read_n_bytes(t_buff *const buff, int fd, size_t n)
{
	size_t	target_read_len;
	ssize_t	read_len;
	ssize_t	total;

	target_read_len = n;
	total = 0;
	while (target_read_len > 0)
	{
		read_len = read(fd, buff->data + buff->len, target_read_len);
		if (read_len < 0 && errno == EINTR)
			continue ;
		else if (read_len < 0)
			return (-1);
		else if (read_len == 0)
			return (total);
		total += read_len;
		target_read_len -= (size_t)read_len;
		buff->len += (size_t)read_len;
	}
	return (total);
}
