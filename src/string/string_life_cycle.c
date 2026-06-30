/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_life_cycle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/30 11:28:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	string_init(t_string *s, size_t initial_cap, const char *str, long n)
{
	s->data = NULL;
	s->cap = 0;
	s->len = 0;
	if (initial_cap > 0)
	{
		s->data = malloc(initial_cap);
		if (!s->data)
			return (false);
		s->cap = initial_cap;
		s->data[0] = '\0';
	}
	if (str)
	{
		if (!string_append_n(s, str, n))
			return (string_free(s), false);
	}
	return (true);
}

void	string_take(t_string *dst, char *src, size_t cap, ssize_t len)
{
	dst->data = src;
	dst->cap = cap;
	if (len < 0)
		dst->len = str_len(src);
	else
		dst->len = (size_t)len;
}

void	string_free(t_string *string)
{
	if (string->data)
		free(string->data);
	string->len = 0;
	string->cap = 0;
	string->data = NULL;
}

void	string_free_void(void *string)
{
	string_free(string);
}
