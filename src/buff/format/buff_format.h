/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_format.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:44 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 22:44:45 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFF_FORMAT_H
# define BUFF_FORMAT_H

# include "libft.h"
# include <stdbool.h>
# include <stddef.h>

typedef struct s_rules
{
	bool	plus;
	bool	space;
	bool	hex_prefix;
	bool	zero_padding;
	bool	right_padding;
	int		precision;
	bool	width_enabled;
	int		width;
	char	conversion;
	bool	is_zero;
}	t_rules;

void	rules_parse(t_rules *rules, const char **fstring);
bool	rules_apply(t_buff *buff, t_rules *rules);

bool	append(t_buff *buff, t_rules *rules, va_list *args);
bool	append_char(t_buff *buff, char c);
bool	append_int(t_buff *buff, int nb);
bool	append_uint(t_buff *buff, unsigned int nb);
bool	append_hex(t_buff *buff, unsigned long nb, bool uppercase);
bool	append_ptr(t_buff *buff, unsigned long nb);

#endif
