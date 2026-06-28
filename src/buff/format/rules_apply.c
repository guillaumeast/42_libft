/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:47 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:31:02 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"
#include <stdlib.h>

/**
 * @brief Applies precision formatting to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static inline bool	apply_precision(t_buff *buff, const t_rules *rules)
{
	size_t	len_without_sign;
	long	zeros_len;
	char	*zeros;
	bool	success;

	if (rules->conversion == 's')
	{
		if (buff->len > (size_t)rules->precision)
			buff->len = (size_t)rules->precision;
		return (true);
	}
	len_without_sign = buff->len - (buff->data[0] == '-');
	if (rules->precision == 0 && buff->len == 1 && buff->data[0] == '0')
		buff->len = 0;
	else if (len_without_sign < (size_t)rules->precision)
	{
		zeros_len = (long)((size_t)rules->precision - len_without_sign);
		zeros = malloc((size_t)zeros_len);
		if (!zeros)
			return (false);
		ft_memset(zeros, '0', (size_t)zeros_len);
		success = buff_insert_n(buff, (buff->data[0] == '-'), zeros, zeros_len);
		return (free(zeros), success);
	}
	return (true);
}

/**
 * @brief Applies plus or space sign formatting for positive numbers.
 *
 * @param buff Pointer to the buffer.
 * @param r Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static inline bool	apply_plus_space(t_buff *buff, const t_rules *rules)
{
	char	sign;

	if (buff->data[0] == '-')
		return (true);
	sign = buff->data[0];
	if (rules->plus)
	{
		sign = '+';
		return (buff_prepend_n(buff, &sign, 1));
	}
	else if (rules->space)
	{
		sign = ' ';
		return (buff_prepend_n(buff, &sign, 1));
	}
	return (true);
}

/**
 * @brief Applies hexadecimal prefix (0x or 0X) to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static inline bool	apply_hex_prefix(t_buff *buff, const t_rules *rules)
{
	char	prefix[2];

	if (buff->data[0] == '(' || rules->is_zero)
		return (true);
	if (buff->len == 0 || (buff->len == 1 && buff->data[0] == '0'))
		return (true);
	prefix[0] = '0';
	if (rules->conversion == 'X')
		prefix[1] = 'X';
	else
		prefix[1] = 'x';
	return (buff_prepend_n(buff, prefix, 2));
}

/**
 * @brief Applies width padding to the buffer.
 *
 * @param b Pointer to the buffer.
 * @param r Pointer to the formatting rules.
 * @return true on success, false on failure.
 */
static inline bool	apply_width(t_buff *buff, const t_rules *rules)
{
	char	*padding;
	size_t	padding_len;
	bool	success;

	if (buff->len >= (size_t)rules->width)
		return (true);
	padding_len = (size_t)rules->width - buff->len;
	padding = malloc(padding_len);
	if (!padding)
		return (false);
	if (rules->zero_padding)
		ft_memset(padding, '0', padding_len);
	else
		ft_memset(padding, ' ', padding_len);
	if (rules->right_padding)
		success = buff_append_n(buff, padding, (long)padding_len);
	else if (rules->zero_padding && buff->len > 0
		&& (buff->data[0] == '-' || rules->plus || rules->space))
		success = buff_insert_n(buff, 1, padding, (long)padding_len);
	else if (rules->zero_padding && buff->len >= 2 && buff->data[0] == '0'
		&& (buff->data[1] == 'x' || buff->data[1] == 'X'))
		success = buff_insert_n(buff, 2, padding, (long)padding_len);
	else
		success = buff_prepend_n(buff, padding, (long)padding_len);
	return (free(padding), success);
}

bool	rules_apply(t_buff *buff, t_rules *rules)
{
	if (buff->len == 1 && buff->data[0] == '0')
		rules->is_zero = true;
	if (rules->precision != -1 && !apply_precision(buff, rules))
		return (false);
	if ((rules->plus || rules->space) && !apply_plus_space(buff, rules))
		return (false);
	if (rules->hex_prefix && !apply_hex_prefix(buff, rules))
		return (false);
	if (rules->width_enabled && !apply_width(buff, rules))
		return (false);
	return (true);
}
