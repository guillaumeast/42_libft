/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 18:56:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/28 14:50:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_str(const char *haystack, const char *needle)
{
	size_t			i;
	size_t			j;
	t_const_cast	cast;

	cast.str = haystack;
	if (needle == NULL || haystack == NULL)
		return (NULL);
	else if (needle[0] == '\0')
		return (cast.res);
	i = 0;
	while (cast.str[i] != '\0')
	{
		j = 0;
		while (cast.str[i + j] && needle[j] && cast.str[i + j] == needle[j])
			j++;
		if (needle[j] == '\0')
			return (cast.res + i);
		i++;
	}
	return (NULL);
}
