/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:39:13 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:21:49 by gastesan         ###   ########.fr       */
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
	while (i < vector->cap)
		f((char *)vector->data + (vector->item_size * i++), del);
}
