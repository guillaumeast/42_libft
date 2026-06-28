/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:55:28 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/28 14:37:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "buckets.h"

bool	hashmap_insert(t_hashmap *map, t_key_value *new)
{
	t_list		bucket;
	size_t		bucket_i;

	bucket_i = map->hash(new->key) % map->buckets.cap;
	bucket = ((t_list *)map->buckets.data)[bucket_i];
	if (bucket != NULL && bucket_contains(bucket, new->key))
		return (bucket_replace(bucket, new, map->del_value), true);
	if (!list_add_end(&bucket, new))
		return (false);
	if (map->buckets.len <= bucket_i)
		map->buckets.len = bucket_i + 1;
	((t_list *)map->buckets.data)[bucket_i] = bucket;
	return (map->size++, true);
}
