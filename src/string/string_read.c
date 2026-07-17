/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/17 15:41:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

bool	string_read_until_c(t_string *string, int fd, char c)
{
	ssize_t	read_len;

	read_len = 1;
	while (read_len > 0)
	{
		if (!string_grow(string, string->len + 2))
		{
			read_len = -1;
			break ;
		}
		read_len = string_read_n_bytes(string, fd, 1);
		if (read_len > 0
			&& string->len > 0
			&& string->data[string->len - 1] == c)
			break ;
	}
	string->data[string->len] = '\0';
	(void)string_adjust(string);
	return (read_len >= 0);
}

bool	string_read_until_n(t_string *string, int fd, size_t n)
{
	ssize_t	read_len;

	if (!string_grow(string, string->len + n + 1))
		return (false);
	read_len = string_read_n_bytes(string, fd, n);
	string->data[string->len] = '\0';
	(void)string_adjust(string);
	return (read_len >= 0);
}

bool	string_read_all(t_string *string, int fd)
{
	ssize_t	read_len;

	read_len = 1;
	while (read_len > 0)
	{
		if (!string_grow(string, string->len + 2))
		{
			read_len = -1;
			break ;
		}
		read_len = string_read_n_bytes(
				string,
				fd,
				string->cap - string->len - 1);
	}
	string->data[string->len] = '\0';
	(void)string_adjust(string);
	return (read_len >= 0);
}
