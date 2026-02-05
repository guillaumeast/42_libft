/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/05 18:32:42 by gastesan         ###   ########.fr       */
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

	va_copy(args_copy, args);
	next_conversion = str_chr(fstring, '%');
	while (next_conversion)
	{
		if (!buff_append(buff, fstring, next_conversion - fstring))
			return (false);
		fstring = next_conversion + 1;
		rules_parse(&rules, &fstring);
		if (rules.conversion == '%')
		{
			if (!buff_append(buff, "%", 1))
				return (false);
		}
		else if (!append(buff, &rules, &args_copy))
			return (false);
		next_conversion = str_chr(fstring, '%');
	}
	va_end(args_copy);
	return (buff_append(buff, fstring, -1));
}
