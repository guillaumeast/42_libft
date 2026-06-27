/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_read_until_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 16:55:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/27 17:41:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static inline bool	string_find_last_char_from(
	char c,
	const char *const s,
	size_t *const i)
{
	size_t	j;

	j = 0;
	while (j <= *i)
	{
		if (s[*i - j] == c)
		{
			*i -= j;
			return (true);
		}
		j++;
	}
	return (false);
}

static inline bool	string_beginning_of_string_is_valid(
	const t_string *const string,
	const char *const s,
	size_t i)
{
	size_t	j;

	if (i >= string->len)
		return (false);
	j = 1;
	while (j <= i)
	{
		if (string->data[string->len - 1 - j] != s[i - j])
			return (false);
		j++;
	}
	return (true);
}

static inline size_t	string_get_size_to_read(
	const t_string *const string,
	const char *const target_string,
	size_t slen)
{
	size_t	i;
	char	c;

	if (string->len == 0 || slen == 0)
		return (slen);
	c = string->data[string->len - 1];
	i = slen - 1;
	while (string_find_last_char_from(c, target_string, &i))
	{
		if (string_beginning_of_string_is_valid(string, target_string, i))
			return (slen - i - 1);
		i--;
	}
	return (slen);
}

bool	string_read_until_s(
	t_string *const string,
	int fd,
	const char *const s,
	ssize_t slen)
{
	size_t	target_read_len;
	ssize_t	read_len;

	if (slen < 0)
		slen = (ssize_t)str_len(s);
	target_read_len = (size_t)slen;
	read_len = 1;
	while (target_read_len > 0 && read_len > 0)
	{
		if (!string_grow(string, string->len + target_read_len + 1))
			return (false);
		read_len = string_read_n_bytes(string, fd, target_read_len);
		if (read_len > 0)
			target_read_len = string_get_size_to_read(string, s, (size_t)slen);
	}
	if (!string_grow(string, string->len + 1))
		return (false);
	string->data[string->len] = '\0';
	(void)string_adjust(string);
	return (read_len >= 0);
}
