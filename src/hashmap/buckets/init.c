/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:33:17 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:23:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"
#include "key_value.h"

void	bucket_free(void *bucket_ptr, void (*del)(void *))
{
	t_node	*entry;

	entry = *(t_node **)bucket_ptr;
	while (entry != NULL)
	{
		key_value_free((t_key_value **)&entry->content, del);
		entry = entry->next;
	}
	list_rm_all((t_list *)bucket_ptr, NULL);
}
bool	buckets_init(t_vector *buckets, size_t init_cap)
{
	if (!vector_init(buckets, sizeof(t_list), init_cap))
		return (false);
	ft_bzero(buckets->data, init_cap * sizeof(t_list));
	return (true);
}

void	buckets_free(t_vector *buckets, void (*del)(void *))
{
	buckets_foreach(buckets, del, bucket_free);
	vector_free(buckets, NULL);
}
