/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_rchr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:49 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/30 23:22:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*str_rchr(const char *s, int c)
{
	char	*last;
	char	target;

	last = NULL;
	target = (char) c;
	while (*s)
	{
		if (*s == target)
			last = (char *)s;
		s++;
	}
	if (target == '\0')
		last = (char *)s;
	return (last);
}
