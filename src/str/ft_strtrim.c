/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:52 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:46:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	ft_is_in_charset(char const c, char const *set);

/**
 * @brief Trims characters from the beginning and end of a string.
 *
 * @param s1 String to trim.
 * @param set Characters to trim.
 * @return Newly allocated trimmed string, or NULL on failure.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_charset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_is_in_charset(s1[end - 1], set))
		end--;
	return (ft_substr(s1, (unsigned int)start, end - start));
}

/**
 * @brief Checks if a character is in a set.
 *
 * @param c Character to check.
 * @param set Character set.
 * @return 1 if found, 0 otherwise.
 */
static int	ft_is_in_charset(char const c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
