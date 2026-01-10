/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:57 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:36:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

/**
 * @brief Locates the first occurrence of a byte in memory.
 *
 * @param s Memory area to search.
 * @param c Byte to search for.
 * @param n Number of bytes to search.
 * @return Pointer to the byte, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		target;
	const unsigned char	*str;
	size_t				i;

	target = (unsigned char) c;
	str = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)str[i] == target)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
