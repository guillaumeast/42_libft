/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:19:31 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"
#include <stdlib.h>

bool	buff_append_format(t_buff *buff, const char *fstring, ...)
{
	va_list	args;
	bool	success;

	va_start(args, fstring);
	success = buff_append_vformat(buff, fstring, args);
	va_end(args);
	return (success);
}

bool	buff_append_vformat(t_buff *buff, const char *fstring, va_list args)
{
	const char	*next_conversion;
	t_rules		rules;
	va_list		args_copy;
	const char	*fstring_p;

	va_copy(args_copy, args);
	fstring_p = fstring;
	next_conversion = str_chr(fstring, '%');
	while (next_conversion)
	{
		if (!buff_append_n(buff, fstring_p, next_conversion - fstring_p))
			return (va_end(args_copy), false);
		fstring_p = next_conversion + 1;
		rules_parse(&rules, &fstring_p);
		if (rules.conversion == '%')
		{
			if (!buff_append_n(buff, "%", 1))
				return (va_end(args_copy), false);
		}
		else if (!append(buff, &rules, &args_copy))
			return (va_end(args_copy), false);
		next_conversion = str_chr(fstring_p, '%');
	}
	return (va_end(args_copy), buff_append_n(buff, fstring_p, -1));
}
