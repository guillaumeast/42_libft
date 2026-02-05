/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_format.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/05 18:02:22 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFF_FORMAT_H
# define BUFF_FORMAT_H

# include "libft.h"

/**
 * @struct s_rules
 * @brief Structure holding format specifier rules for printf-like formatting.
 *
 * @var s_rules::plus Display '+' sign for positive numbers.
 * @var s_rules::space Display space before positive numbers.
 * @var s_rules::hex_prefix Display '0x' or '0X' prefix for hex numbers.
 * @var s_rules::zero_padding Pad with zeros instead of spaces.
 * @var s_rules::right_padding Right-align the output.
 * @var s_rules::precision Precision value, -1 if not set.
 * @var s_rules::width_enabled Width specifier is enabled.
 * @var s_rules::width Minimum field width.
 * @var s_rules::conversion Conversion specifier character.
 * @var s_rules::is_zero Value is zero (used for special cases).
 */
typedef struct s_rules
{
	/** @brief Display '+' sign for positive numbers. */
	bool	plus;
	/** @brief Display space before positive numbers. */
	bool	space;
	/** @brief Display '0x' or '0X' prefix for hex numbers. */
	bool	hex_prefix;
	/** @brief Pad with zeros instead of spaces. */
	bool	zero_padding;
	/** @brief Right-align the output. */
	bool	right_padding;
	/** @brief Precision value, -1 if not set. */
	int		precision;
	/** @brief Width specifier is enabled. */
	bool	width_enabled;
	/** @brief Minimum field width. */
	int		width;
	/** @brief Conversion specifier character. */
	char	conversion;
	/** @brief Value is zero (used for special cases). */
	bool	is_zero;
}	t_rules;

/**
 * @brief Parses format specifiers from a format string.
 *
 * @param rules Pointer to the rules structure to populate.
 * @param fstring Pointer to format string pointer (advanced by parsing).
 */
void	rules_parse(t_rules *rules, const char **fstring);

/**
 * @brief Applies formatting rules to a buffer.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the rules structure.
 * @return true on success, false on failure.
 */
bool	rules_apply(t_buff *buff, t_rules *rules);

/**
 * @brief Appends formatted argument to buffer based on rules.
 *
 * @param buff Pointer to the buffer.
 * @param rules Pointer to the formatting rules.
 * @param args Pointer to the variable argument list.
 * @return true on success, false on failure.
 */
bool	append(t_buff *buff, t_rules *rules, va_list *args);

/**
 * @brief Appends a character to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param c Character to append.
 * @return true on success, false on failure.
 */
bool	append_char(t_buff *buff, char c);

/**
 * @brief Appends an integer to the buffer as a string.
 *
 * @param buff Pointer to the buffer.
 * @param nb Integer to append.
 * @return true on success, false on failure.
 */
bool	append_int(t_buff *buff, int nb);

/**
 * @brief Appends an unsigned integer to the buffer as a string.
 *
 * @param buff Pointer to the buffer.
 * @param nb Unsigned integer to append.
 * @return true on success, false on failure.
 */
bool	append_uint(t_buff *buff, unsigned int nb);

/**
 * @brief Appends a number in hexadecimal format to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param nb Number to convert.
 * @param uppercase Use uppercase letters if true.
 * @return true on success, false on failure.
 */
bool	append_hex(t_buff *buff, unsigned long nb, bool uppercase);

/**
 * @brief Appends a pointer address to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param nb Pointer value as unsigned long.
 * @return true on success, false on failure.
 */
bool	append_ptr(t_buff *buff, unsigned long nb);

#endif
