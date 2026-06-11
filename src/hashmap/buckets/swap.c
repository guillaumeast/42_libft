/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:50:24 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 15:50:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buckets_swap(t_vector *buckets1, t_vector *buckets2)
{
	t_vector	temp;

	temp = *buckets1;
	*buckets1 = *buckets2;
	*buckets2 = temp;
}
