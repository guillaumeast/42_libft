/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/14 21:07:55 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

long	ft_atol(const char *str)
{
	size_t	i;
	int		sign;
	long	result;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((long)(result * sign));
}

size_t	ft_atozu(const char *str)
{
	size_t	i;
	size_t	result;
	size_t	digit;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = (size_t)(str[i] - '0');
		if (result > (SIZE_MAX - digit) / 10)
			return (SIZE_MAX);
		result = result * 10 + digit;
		i++;
	}
	return (result);
}
