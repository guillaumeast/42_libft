/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:37:59 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:25:46 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer.
 *
 * @param str String to convert.
 * @return The converted integer value.
 */
int	ft_atoi(const char *str)
{
	return ((int)ft_atol(str));
}

/**
 * @brief Converts an integer to a string.
 *
 * @param n Integer to convert.
 * @return Newly allocated string, or NULL on failure.
 */
char	*ft_itoa(int n)
{
	return (ft_ltoa((long) n));
}

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param n Unsigned integer to convert.
 * @return Newly allocated string, or NULL on failure.
 */
char	*ft_utoa(unsigned int n)
{
	return (ft_ltoa((long) n));
}
