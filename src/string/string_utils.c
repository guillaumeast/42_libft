/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/27 18:58:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	string_adjust(t_string *const string)
{
	char	*new_data;
	size_t	new_cap;

	if (string->cap == string->len + 1)
		return (true);
	new_cap = string->len + 1;
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

ssize_t	string_get_index_c(const t_string *const string, char c)
{
	size_t	i;

	i = 0;
	while (i < string->len)
	{
		if (string->data[i] == c)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}

ssize_t	string_get_index_s(
	const t_string *const string,
	const char *const s,
	ssize_t slen)
{
	size_t	i;
	size_t	j;

	if (slen == 0 || s[0] == '\0')
		return ((ssize_t)string->len);
	if (slen < 0)
		slen = (ssize_t)str_len(s);
	if ((size_t)slen > string->len)
		return (-1);
	i = 0;
	while (i < string->len)
	{
		j = 0;
		while (j < (size_t)slen
			&& i + j < string->len
			&& string->data[i + j] == s[j])
			j++;
		if (j == (size_t)slen)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}
