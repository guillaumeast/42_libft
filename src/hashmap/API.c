/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:56:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:27:43 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "key_value.h"
#include "priv_hashmap.h"

bool	hashmap_put(t_hashmap *map, char *key, void *value)
{
	t_key_value	*pair;

	if (map->size + 1 > map->buckets.cap && !hashmap_resize(map))
		return (false);
	pair = key_value_new(key, value);
	if (pair == NULL)
		return (false);
	if (!hashmap_insert(map, pair))
		return (key_value_free(&pair, map->del_value), false);
	return (true);
}

void	*hashmap_get(t_hashmap *map, char *key)
{
	t_node	*entry;

	entry = ((t_list*)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return (((t_key_value *)entry->content)->value);
		entry = entry->next;
	}
	return (NULL);
}

bool	hashmap_remove(t_hashmap *map, char *key)
{
	t_key_value	*pair;
	t_node		*entry;
	t_list		bucket;
	size_t		bucket_i;

	bucket_i = map->hash(key) % map->buckets.cap;
	bucket = ((t_list*)map->buckets.data)[bucket_i];
	entry = bucket;
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
		{
			pair = entry->content;
			key_value_free(&pair, map->del_value);
			list_rm(&bucket, entry, NULL);
			((t_list*)map->buckets.data)[bucket_i] = bucket;
			return (map->size--, true);
		}
		entry = entry->next;
	}
	return (false);
}

bool	hashmap_contains(t_hashmap *map, char *key)
{
	t_node	*entry;

	entry = ((t_list*)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return (true);
		entry = entry->next;
	}
	return (false);
}
