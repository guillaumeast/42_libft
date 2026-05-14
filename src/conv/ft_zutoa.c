/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zutoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 21:18:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/14 21:23:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_len(size_t n);
static void		populate(size_t n, char *str, size_t i);

char	*ft_zutoa(size_t n)
{
	size_t	len;
	char	*res;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	populate(n, res, len - 1);
	return (res);
}

/**
 * @brief Calculates the string length needed for a size_t number.
 *
 * @param n Size_t number.
 * @return Length of the decimal representation.
 */
static size_t	get_len(size_t n)
{
	size_t	len;

	len = 1;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

/**
 * @brief Recursively populates a string with digits from a size_t.
 *
 * @param n Size_t number to convert.
 * @param str Destination string.
 * @param i Current index to write to.
 */
static void	populate(size_t n, char *str, size_t i)
{
	size_t	mod;

	if (n >= 10)
		populate(n / 10, str, i - 1);
	mod = n % 10;
	str[i] = (char)mod + '0';
}
