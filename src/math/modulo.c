/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 21:26:58 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/15 21:26:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	modulo(long a, size_t b)
{
	long	res;

	res = a % (long)b;
	if (res < 0)
		res += (long)b;
	return ((size_t)res);
}
