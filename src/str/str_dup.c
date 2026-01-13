/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 17:10:39 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	void	str_cpy(char *dst, const char *src);

char	*str_dup(const char *s1)
{
	char	*res;

	res = malloc(str_len(s1) + 1);
	if (!res)
		return (NULL);
	str_cpy(res, s1);
	return (res);
}

/**
 * @brief Copies a string to a destination.
 *
 * @param dst Destination buffer.
 * @param src Source string.
 */
static	void	str_cpy(char *dst, const char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}
