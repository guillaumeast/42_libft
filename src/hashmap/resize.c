/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:53:40 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:28:35 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"
#include "priv_hashmap.h"

static void	hashmap_restore(t_hashmap *map, size_t prev_size, t_vector *backup)
{
	map->size = prev_size;
	buckets_detach(&map->buckets);
	buckets_free(&map->buckets, map->del_value);
	buckets_swap(&map->buckets, backup);
}

static bool	hashmap_redistribution(t_hashmap *map, t_vector *prev_buckets)
{
	t_key_value	*pair;
	t_node		*entry;
	size_t		bucket_i;

	bucket_i = 0;
	while (bucket_i < prev_buckets->len)
	{
		entry = ((t_list*)prev_buckets->data)[bucket_i];
		while (entry != NULL)
		{
			pair = entry->content;
			if (pair == NULL)
				return (false);
			if (!hashmap_insert(map, pair))
				return (false);
			entry = entry->next;
		}
		bucket_i++;
	}	
	return (true);
}

bool	hashmap_resize(t_hashmap *map)
{
	size_t		prev_size;
	t_vector 	prev_buckets;
	
	prev_size = map->size;
	if (!buckets_init(&prev_buckets, map->buckets.cap * 2))
		return (false);
	map->size = 0;
	buckets_swap(&map->buckets, &prev_buckets);
	if (!hashmap_redistribution(map, &prev_buckets))
		return (hashmap_restore(map, prev_size, &prev_buckets), false);
	buckets_detach(&prev_buckets);
	buckets_free(&prev_buckets, map->del_value);
	return (true);
}
