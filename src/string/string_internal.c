/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_internal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 14:13:43 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:08:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_STRING_CAP	128
#define STRING_GROWTH		2

size_t	string_get_required_cap(size_t current_cap, size_t target_cap)
{
	size_t	new_cap;

	if (target_cap == 0)
		return (current_cap);
	if (current_cap == 0)
		new_cap = DEFAULT_STRING_CAP;
	else
		new_cap = current_cap;
	while (new_cap <= target_cap)
		new_cap *= STRING_GROWTH;
	return (new_cap);
}

bool	string_grow(t_string *string, size_t target_cap)
{
	size_t	new_cap;
	char	*new_data;

	new_cap = string_get_required_cap(string->cap, target_cap);
	if (new_cap <= string->cap)
		return (true);
	new_data = malloc(new_cap);
	if (!new_data)
		return (false);
	if (string->data)
		ft_memcpy(new_data, string->data, string->len + 1);
	else
		new_data[0] = '\0';
	free(string->data);
	string->data = new_data;
	string->cap = new_cap;
	return (true);
}

ssize_t	string_read_n_bytes(t_string *string, int fd, size_t n)
{
	size_t	target_read_len;
	ssize_t	read_len;
	ssize_t	total;

	target_read_len = n;
	total = 0;
	while (target_read_len > 0)
	{
		read_len = read(fd, string->data + string->len, target_read_len);
		if (read_len < 0 && errno == EINTR)
			continue ;
		else if (read_len < 0)
			return (-1);
		else if (read_len == 0)
			return (total);
		total += read_len;
		target_read_len -= (size_t)read_len;
		string->len += (size_t)read_len;
	}
	return (total);
}
