/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max_abs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 02:28:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/23 03:06:28 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"

long	min(long a, long b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

long	max(long a, long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

size_t	absolute(long nbr)
{
	if (nbr < 0)
		nbr *= -1;
	return ((size_t)nbr);
}
