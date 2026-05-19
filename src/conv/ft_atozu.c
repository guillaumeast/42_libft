/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atozu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:05 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:27:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

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
