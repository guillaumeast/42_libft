/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split_on_char.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:39:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/07 12:54:26 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_split_priv.h"

static inline bool	string_split_on_char_keep_empties(
			const t_string *src,
			char c,
			t_vector *out)
{
	size_t	len;
	size_t	start;

	(void)vector_init(out, sizeof(t_string), 0);
	if (src->len == 0)
		return (string_add_to_vector(src, 0, 0, out));
	start = 0;
	while (start < src->len)
	{
		len = 0;
		while (start + len < src->len && src->data[start + len] != c)
			len++;
		if (!string_add_to_vector(src, start, len, out))
			return (false);
		start += len + 1;
	}
	if (src->data[src->len - 1] == c)
		return (string_add_to_vector(src, src->len, 0, out));
	return (true);
}

static inline bool	string_split_on_char_skip_empties(
			const t_string *src,
			char c,
			t_vector *out)
{
	size_t	len;
	size_t	start;

	(void)vector_init(out, sizeof(t_string), 0);
	start = 0;
	while (start < src->len)
	{
		while (start < src->len && src->data[start] == c)
			start++;
		if (start >= src->len)
			break ;
		len = 1;
		while (start + len < src->len && src->data[start + len] != c)
			len++;
		if (!string_add_to_vector(src, start, len, out))
			return (false);
		start += len;
	}
	return (true);
}

bool	string_split_on_char(
			const t_string *src,
			char c,
			bool skip_empty_entries,
			t_vector *out)
{
	if (skip_empty_entries == true)
		return (string_split_on_char_skip_empties(src, c, out));
	return (string_split_on_char_keep_empties(src, c, out));
}
