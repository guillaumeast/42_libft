/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 02:28:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:36:14 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Returns the minimum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The smaller value.
 */
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

/**
 * @brief Returns the maximum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The larger value.
 */
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
