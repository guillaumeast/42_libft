/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:55 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 17:13:04 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*str_sub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	min_len;
	char	*res;

	if (!s)
		return (NULL);
	if (start > str_len(s))
		return (ft_calloc(1, 1));
	min_len = str_len(s + start);
	if (min_len < len)
		res = malloc(min_len + 1);
	else
		res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
