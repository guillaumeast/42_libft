/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_read_until_s.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/27 16:55:42 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/27 17:41:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buff_internal.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static inline bool	buff_find_last_char_from(
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

static inline bool	buff_beginning_of_string_is_valid(
	const t_buff *const buff,
	const char *const s,
	size_t i)
{
	size_t	j;

	if (i >= buff->len)
		return (false);
	j = 1;
	while (j <= i)
	{
		if (buff->data[buff->len - 1 - j] != s[i - j])
			return (false);
		j++;
	}
	return (true);
}

static inline size_t	buff_get_size_to_read(
	const t_buff *const buff,
	const char *const target_string,
	size_t slen)
{
	size_t	i;
	char	c;

	if (buff->len == 0 || slen == 0)
		return (slen);
	c = buff->data[buff->len - 1];
	i = slen - 1;
	while (buff_find_last_char_from(c, target_string, &i))
	{
		if (buff_beginning_of_string_is_valid(buff, target_string, i))
			return (slen - i - 1);
		i--;
	}
	return (slen);
}

bool	buff_read_until_s(
	t_buff *const buff,
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
		if (!buff_grow(buff, buff->len + target_read_len))
			return (false);
		read_len = buff_read_n_bytes(buff, fd, target_read_len);
		if (read_len > 0)
			target_read_len = buff_get_size_to_read(buff, s, (size_t)slen);
	}
	(void)buff_adjust(buff);
	return (read_len >= 0);
}
