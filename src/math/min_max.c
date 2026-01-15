/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 02:28:23 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/15 14:36:19 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
