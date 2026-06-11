/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:39:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 15:39:36 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	buckets_foreach(
	t_vector *vector,
	void (*del)(void *),
	void (*f)(void *, void (*del)(void *)))
{
	size_t	i;

	i = 0;
	while (i < vector->len)
		f((char *)vector->data + (vector->item_size * i++), del);
}
