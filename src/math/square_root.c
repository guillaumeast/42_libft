/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_root.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 13:35:16 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:36:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Calculates the exact integer square root.
 *
 * @param nb Number to find square root of.
 * @return Exact square root if perfect square, -1 otherwise.
 */
int	square_root_exact(int nb)
{
	int	i;

	if (nb <= 0)
		return (-1);
	i = 1;
	while (i <= nb / i)
	{
		if (i * i == nb)
			return (i);
		i++;
	}
	return (-1);
}

/**
 * @brief Calculates the nearest integer square root.
 *
 * @param nb Number to find square root of.
 * @return Nearest integer square root, -1 if nb <= 0.
 */
int	square_root_rounded(int nb)
{
	int	low;
	int	high;

	if (nb <= 0)
		return (-1);
	high = 1;
	while (high <= nb / high)
		high++;
	low = high - 1;
	if ((nb / low) - low < high - (nb / high))
		return (low);
	return (high);
}
