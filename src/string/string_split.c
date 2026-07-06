/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:39:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/06 19:47:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	string_split_at(
			const t_string *src,
			size_t index,
			t_string *out_before,
			t_string *out_after)
{
	if (index >= src->len)
	{
		if (!string_dup(out_before, src))
			return (false);
		if (!string_init(out_after, 1, "", 0))
			return (string_free(out_before), false);
		return (true);
	}
	if (!string_init(out_before, 0, src->data, (long)index))
		return (false);
	if (!string_init(out_after, 0, src->data + index, (long)(src->len - index)))
		return (string_free(out_before), false);
	return (true);
}

static inline bool	string_add_to_vector(
						const t_string *src,
						size_t start,
						size_t len,
						t_vector *out)
{
	t_string	string;

	if (!string_init(&string, 0, src->data + start, (long)len))
	{
		vector_free(out, string_free_void);
		return (false);
	}
	if (!vector_push(out, &string))
	{
		string_free(&string);
		vector_free(out, string_free_void);
		return (false);
	}
	return (true);
}

bool	string_split_on_char(const t_string *src, char c, t_vector *out)
{
	size_t		len;
	size_t		start;

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

static inline bool	string_is_sep(
						const t_string *src,
						size_t i,
						const char *sep)
{
	size_t	j;

	j = 0;
	while (i + j < src->len && sep[j] != '\0')
	{
		if (src->data[i + j] != sep[j])
			return (false);
		j++;
	}
	return (sep[j] == '\0');
}

bool	string_split_on_string(
			const t_string *src,
			const char *sep,
			t_vector *out)
{
	size_t		sep_len;
	size_t		len;
	size_t		start;

	(void)vector_init(out, sizeof(t_string), 0);
	sep_len = str_len(sep);
	if (sep_len == 0)
		return (string_add_to_vector(src, 0, src->len, out));
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
