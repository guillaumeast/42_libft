/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split_on_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:39:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/07 13:53:46 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_split_priv.h"

static inline bool	string_split_on_string_skip_empties(
						const t_string *src,
						const char *sep,
						t_vector *out)
{
	size_t		sep_len;
	size_t		len;
	size_t		start;

	(void)vector_init(out, sizeof(t_string), 0);
	sep_len = str_len(sep);
	if (sep_len == 0 && src->len > 0)
		return (string_add_to_vector(src, 0, src->len, out));
	else if (sep_len == 0)
		return (true);
	start = 0;
	while (start < src->len)
	{
		while (string_is_sep(src, start, sep))
			start += sep_len;
		if (start >= src->len)
			break ;
		len = 1;
		while (start + len < src->len && !string_is_sep(src, start + len, sep))
			len++;
		if (!string_add_to_vector(src, start, len, out))
			return (false);
		start += len + sep_len;
	}
	return (true);
}

static inline bool	string_split_on_string_keep_empties(
						const t_string *src,
						const char *sep,
						t_vector *out)
{
	size_t		sep_len;
	size_t		len;
	size_t		start;

	(void)vector_init(out, sizeof(t_string), 0);
	sep_len = str_len(sep);
	if (sep_len == 0 || src->len == 0)
		return (string_add_to_vector(src, 0, src->len, out));
	start = 0;
	while (start <= src->len)
	{
		len = 0;
		while (start + len < src->len && !string_is_sep(src, start + len, sep))
			len++;
		if (!string_add_to_vector(src, start, len, out))
			return (false);
		if (start + len >= src->len)
			break ;
		start += len + sep_len;
	}
	return (true);
}

bool	string_split_on_string(
			const t_string *src,
			const char *sep,
			bool keep_empty_entries,
			t_vector *out)
{
	if (keep_empty_entries == true)
		return (string_split_on_string_keep_empties(src, sep, out));
	return (string_split_on_string_skip_empties(src, sep, out));
}
