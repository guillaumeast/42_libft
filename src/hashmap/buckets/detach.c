/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detach.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:42:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:26:33 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"

void	bucket_detach(void *bucket, void (*_)(void *))
{
	t_node	*entry;

	entry = *(t_node **)bucket;
	while (entry != NULL)
	{
		entry->content = NULL;
		entry = entry->next;
	}
}

void	buckets_detach(t_vector *buckets)
{
	buckets_foreach(buckets, NULL, bucket_detach);
}
