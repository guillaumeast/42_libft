/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim_leading.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 13:03:30 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/05 13:04:28 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int	ft_is_in_charset(char const c, char const *set);

char	*str_trim_leading(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_is_in_charset(s1[start], set))
		start++;
	end = str_len(s1);
	return (str_sub(s1, (unsigned int)start, end - start));
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
