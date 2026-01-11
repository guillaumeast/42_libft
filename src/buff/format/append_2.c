/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:41 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:29:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	append_char(t_buff *buff, char c)
{
	return (buff_append(buff, &c, 1));
}

bool	append_int(t_buff *buff, int nb)
{
	char	*tmp;
	bool	success;

	tmp = ft_itoa(nb);
	if (!tmp)
		return (false);
	success = buff_append(buff, tmp, -1);
	free(tmp);
	return (success);
}

bool	append_uint(t_buff *buff, unsigned int nb)
{
	char	*tmp;
	bool	success;

	tmp = ft_utoa(nb);
	if (!tmp)
		return (false);
	success = buff_append(buff, tmp, -1);
	free(tmp);
	return (success);
}

bool	append_hex(t_buff *buff, unsigned long nb, bool uppercase)
{
	char				*tmp;
	bool				success;
	static const char	upperbase[] = "0123456789ABCDEF";
	static const char	lowerbase[] = "0123456789abcdef";

	if (uppercase)
		tmp = ft_ultoa_base(nb, upperbase);
	else
		tmp = ft_ultoa_base(nb, lowerbase);
	if (!tmp)
		return (false);
	success = buff_append(buff, tmp, -1);
	free(tmp);
	return (success);
}

/**
 * @brief Appends a pointer address to the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param nb Pointer value as unsigned long.
 * @return true on success, false on failure.
 */
bool	append_ptr(t_buff *buff, unsigned long nb)
{
	if (nb == 0)
		return (buff_append(buff, "(nil)", 5));
	return (append_hex(buff, nb, false));
}
