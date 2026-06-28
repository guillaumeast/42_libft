/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_ops_n.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:32:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "string_internal.h"
#include <stdlib.h>

bool	string_prepend_n(t_string *s, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	new_cap = string_get_required_cap(s->cap, s->len + strlen + 1);
	if (new_cap > s->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		s->cap = new_cap;
		ft_memcpy(new_data + strlen, s->data, s->len);
		free(s->data);
		s->data = new_data;
	}
	else
		ft_memmove(s->data + strlen, s->data, s->len);
	ft_memcpy(s->data, str, strlen);
	s->len = s->len + strlen;
	s->data[s->len] = '\0';
	return (true);
}

bool	string_insert_n(t_string *s, size_t index, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	new_cap = string_get_required_cap(s->cap, s->len + strlen + 1);
	if (new_cap > s->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		s->cap = new_cap;
		ft_memcpy(new_data, s->data, index);
		ft_memcpy(new_data + index + strlen, s->data + index, s->len - index);
		free(s->data);
		s->data = new_data;
	}
	else
		ft_memmove(s->data + index + strlen, s->data + index, s->len - index);
	ft_memcpy(s->data + index, str, strlen);
	s->len = s->len + strlen;
	return (s->data[s->len] = '\0', true);
}

bool	string_append_n(t_string *s, const char *str, long n)
{
	size_t	strlen;

	if (n < 0)
		strlen = str_len(str);
	else
		strlen = (size_t)n;
	if (!string_grow(s, s->len + strlen + 1))
		return (false);
	ft_memcpy(s->data + s->len, str, strlen);
	s->len = s->len + strlen;
	s->data[s->len] = '\0';
	return (true);
}

bool	string_dup_n(t_string *dst, const t_string *src, size_t n)
{
	if (n > src->len)
		n = src->len;
	dst->len = 0;
	if (!string_append_n(dst, src->data, (long)n))
	{
		string_free(dst);
		return (false);
	}
	return (true);
}
