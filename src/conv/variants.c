/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:37:59 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:25:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	return ((int)ft_atol(str));
}

char	*ft_itoa(int n)
{
	return (ft_ltoa((long) n));
}

char	*ft_utoa(unsigned int n)
{
	return (ft_ltoa((long) n));
}
