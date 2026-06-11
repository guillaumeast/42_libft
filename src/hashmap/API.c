/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:56:39 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:45:37 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "key_value.h"
#include "priv_hashmap.h"

bool	hashmap_put(t_hashmap *map, const char *key, void *value)
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

t_key_value	*hashmap_get(t_hashmap *map, const char *key)
{
	t_node	*entry;

	entry = ((t_list*)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return ((t_key_value *)entry->content);
		entry = entry->next;
	}
	return (NULL);
}

t_key_value	**hashmap_get_all(t_hashmap *map)
{
	t_key_value	**res;
	size_t		pair_i;
	t_node		*entry;
	size_t		bucket_i;
	
	res = malloc(sizeof(t_key_value *) * (map->size + 1));
	if (res == NULL)
		return (NULL);
	bucket_i = 0;
	pair_i = 0;
	while (bucket_i < map->buckets.len)
	{
		entry = ((t_list*)map->buckets.data)[bucket_i];
		while (entry != NULL)
		{
			res[pair_i++] = entry->content;
			entry = entry->next;
		}		
		++bucket_i;
	}
	res[pair_i] = NULL;
	return (res);
}

bool	hashmap_remove(t_hashmap *map, const char *key)
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

bool	hashmap_contains(t_hashmap *map, const char *key)
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
