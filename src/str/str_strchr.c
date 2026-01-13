/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_strchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/13 17:10:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*str_chr(const char *s, int c)
{
	char	target;

	target = (char) c;
	while (*s)
	{
		if (*s == target)
			return ((char *) s);
		s++;
	}
	if (target == '\0')
		return ((char *) s);
	return (NULL);
}
