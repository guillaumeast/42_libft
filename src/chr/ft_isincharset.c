/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isincharset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 21:30:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:21:38 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

/**
 * @brief Checks if a character is present in a character set.
 *
 * @param c Character to check.
 * @param charset Null-terminated string of characters to match against.
 * @return true if found in charset, false otherwise.
 */
bool	ft_isincharset(char c, const char *charset)
{
	while (*charset)
	{
		if (*charset == c)
			return (true);
		charset++;
	}
	return (false);
}
