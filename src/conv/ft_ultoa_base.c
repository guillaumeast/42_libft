/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:38:08 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:25:16 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	get_base_len(const char *base);
static size_t	get_res_len(unsigned long n, size_t base_len);

// TODO: préciser que c'est au caller de
/**
 * @brief Converts an unsigned long to a string in a given base.
 *
 * @param n Number to convert.
 * @param base String representing the base characters.
 * @return Newly allocated string, or NULL on failure.
 */
char	*ft_ultoa_base(unsigned long n, const char *base)
{
	size_t	base_len;
	size_t	res_len;
	char	*res;

	if (!base)
		return (NULL);
	base_len = get_base_len(base);
	if (base_len < 2)
		return (NULL);
	res_len = get_res_len(n, base_len);
	res = malloc(res_len + 1);
	if (!res)
		return (NULL);
	res[res_len] = '\0';
	while (res_len-- > 0)
	{
		res[res_len] = base[n % base_len];
		n /= base_len;
	}
	return (res);
}

/**
 * @brief Calculates the length of a base string.
 *
 * @param base Base string.
 * @return Length of the base.
 */
static size_t	get_base_len(const char *base)
{
	size_t	len;

	len = 0;
	while (base[len])
		len++;
	return (len);
}

/**
 * @brief Calculates the result string length for a number in a given base.
 *
 * @param n Number to convert.
 * @param base_len Length of the base.
 * @return Required string length.
 */
static size_t	get_res_len(unsigned long n, size_t base_len)
{
	size_t	len;

	len = 1;
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}
