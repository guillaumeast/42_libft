/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/11 16:23:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	string_init(
	t_string *const s,
	size_t initial_cap,
	const char *const str,
	long n)
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

void	string_free(t_string *const string)
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
