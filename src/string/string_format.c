/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/05 18:32:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	string_append_format(
	t_string *const string,
	const char *const fstring,
	...)
{
	va_list	args;
	bool	success;

	va_start(args, fstring);
	success = string_append_vformat(string, fstring, args);
	va_end(args);
	return (success);
}

bool	string_append_vformat(
	t_string *const string,
	const char *const fstring,
	va_list args)
{
	t_buff	buff;
	bool	success;

	if (!buff_init(&buff, 0, NULL, 0))
		return (false);
	success = buff_append_vformat(&buff, fstring, args);
	if (success)
		success = string_append_n(string, buff.data, (long)buff.len);
	buff_free(&buff);
	return (success);
}
