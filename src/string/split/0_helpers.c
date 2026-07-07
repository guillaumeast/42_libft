/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_helpers.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:39:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/07 12:59:52 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	string_add_to_vector(
			const t_string *src,
			size_t start,
			size_t len,
			t_vector *out)
{
	t_string	string;

	if (len == 0)
	{
		if (!string_init(&string, 0, "", 0))
			return (vector_free(out, string_free_void), false);
	}
	else if (!string_init(&string, 0, src->data + start, (long)len))
		return (vector_free(out, string_free_void), false);
	if (!vector_push(out, &string))
	{
		string_free(&string);
		vector_free(out, string_free_void);
		return (false);
	}
	return (true);
}

bool	string_is_sep(
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
