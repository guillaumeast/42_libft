/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:50 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:01:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buff_format.h"

static void	parse_flags(t_rules *rules, const char **fstring);
static void	parse_width(t_rules *rules, const char **fstring);
static void	parse_precision(t_rules *rules, const char **fstring);
static void	normalize(t_rules *rules);

/**
 * @brief Parses format specifiers from a format string into rules structure.
 *
 * @param rules Pointer to the rules structure to populate.
 * @param fstring Pointer to format string pointer (advanced during parsing).
 */
void	rules_parse(t_rules *rules, const char **fstring)
{
	const char	conversion_set[] = "csdiuxXp";

	rules->plus = false;
	rules->space = false;
	rules->hex_prefix = false;
	rules->zero_padding = false;
	rules->right_padding = false;
	rules->precision = -1;
	rules->width_enabled = false;
	rules->width = -1;
	rules->conversion = '\0';
	rules->is_zero = false;
	if (**fstring != '%')
	{
		parse_flags(rules, fstring);
		if (**fstring != '.' && !ft_isincharset(**fstring, conversion_set))
			parse_width(rules, fstring);
		if (**fstring == '.')
			parse_precision(rules, fstring);
	}
	rules->conversion = **fstring;
	normalize(rules);
	(*fstring)++;
}

/**
 * @brief Parses flag characters from the format string.
 *
 * @param rules Pointer to the rules structure.
 * @param fstring Pointer to format string pointer.
 */
static void	parse_flags(t_rules *rules, const char **fstring)
{
	const char	flag_set[] = "-0# +";
	char		c;

	while (ft_isincharset(**fstring, flag_set))
	{
		c = **fstring;
		if (c == '-')
			rules->right_padding = true;
		else if (c == '0')
			rules->zero_padding = true;
		else if (c == '#')
			rules->hex_prefix = true;
		else if (c == ' ')
			rules->space = true;
		else if (c == '+')
			rules->plus = true;
		(*fstring)++;
	}
}

/**
 * @brief Parses width specifier from the format string.
 *
 * @param rules Pointer to the rules structure.
 * @param fstring Pointer to format string pointer.
 */
static void	parse_width(t_rules *rules, const char **fstring)
{
	rules->width_enabled = true;
	rules->width = ft_atoi(*fstring);
	while (ft_isdigit(**fstring))
		(*fstring)++;
}

/**
 * @brief Parses precision specifier from the format string.
 *
 * @param rules Pointer to the rules structure.
 * @param fstring Pointer to format string pointer.
 */
static void	parse_precision(t_rules *rules, const char **fstring)
{
	(*fstring)++;
	rules->precision = ft_atoi(*fstring);
	while (ft_isdigit(**fstring))
		(*fstring)++;
}

/**
 * @brief Normalizes rules based on conversion specifier constraints.
 *
 * @param rules Pointer to the rules structure.
 */
static void	normalize(t_rules *rules)
{
	char	conv;

	conv = rules->conversion;
	if (conv != 'x' && conv != 'X' && conv != 'p')
		rules->hex_prefix = false;
	if (conv == 'p')
	{
		rules->hex_prefix = true;
		rules->precision = -1;
	}
	if (conv == 'c')
		rules->precision = -1;
	if (conv != 'd' && conv != 'i')
		rules->plus = false;
	if ((conv != 'd' && conv != 'i') || rules->plus)
		rules->space = false;
	if (rules->width_enabled && rules->width < 0)
	{
		rules->right_padding = true;
		rules->width = -rules->width;
	}
	if (rules->right_padding || rules->precision != -1)
		rules->zero_padding = false;
}
