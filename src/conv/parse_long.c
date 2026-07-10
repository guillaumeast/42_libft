/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_long.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 21:26:28 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/10 21:26:29 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <limits.h>

bool	parse_long(char *s, long *out)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (*s == '\0')
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9' || result > (LONG_MAX - (*s - '0')) / 10)
			return (false);
		result = result * 10 + (*s - '0');
		s++;
	}
	result *= sign;
	*out = result;
	return (true);
}
