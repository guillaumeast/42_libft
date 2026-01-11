/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:29:42 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"

static bool	append_str(t_buff *buff, t_rules *rules, const char *str);

bool	append(t_buff *buff, t_rules *rules, va_list *args)
{
	t_buff	tmp_buff;
	bool	success;

	buff_init(&tmp_buff, 0);
	success = false;
	if (rules->conversion == 'c')
		success = append_char(&tmp_buff, va_arg(*args, int));
	else if (rules->conversion == 's')
		success = append_str(&tmp_buff, rules, va_arg(*args, char *));
	else if (rules->conversion == 'd' || rules->conversion == 'i')
		success = append_int(&tmp_buff, va_arg(*args, int));
	else if (rules->conversion == 'u')
		success = append_uint(&tmp_buff, va_arg(*args, unsigned int));
	else if (rules->conversion == 'x')
		success = append_hex(&tmp_buff, va_arg(*args, unsigned int), false);
	else if (rules->conversion == 'X')
		success = append_hex(&tmp_buff, va_arg(*args, unsigned int), true);
	else if (rules->conversion == 'p')
		success = append_ptr(&tmp_buff, (unsigned long)va_arg(*args, void *));
	if (success)
		success = rules_apply(&tmp_buff, rules);
	if (success)
		success = buff_append(buff, tmp_buff.data, (long)tmp_buff.len);
	buff_free(&tmp_buff);
	return (success);
}

/**
 * @brief Appends a string to the buffer with null handling.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @param str String to append (can be NULL).
 * @return true on success, false on failure.
 */
static bool	append_str(t_buff *buff, t_rules *rules, const char *str)
{
	if (!str)
	{
		if (rules->precision != -1 && rules->precision < 6)
			return (true);
		else
			return (buff_append(buff, "(null)", 6));
	}
	else
		return (buff_append(buff, str, -1));
}
