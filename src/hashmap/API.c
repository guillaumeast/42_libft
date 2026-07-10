/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   API.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:34:55 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/11 01:11:44 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "key_value.h"
#include "priv_hashmap.h"

bool	hashmap_put(t_hashmap *map, const char *key, void *value)
{
	const void	*existing;
	t_key_value	*pair;

	existing = hashmap_get_const(map, key);
	if (existing && existing == value)
		return (true);
	if (hashmap_need_resize(map, key) && !hashmap_resize(map))
		return (false);
	pair = key_value_new(key, value);
	if (pair == NULL)
		return (false);
	if (!hashmap_insert(map, pair))
		return (key_value_free(&pair, NULL), false);
	return (true);
}

void	*hashmap_get(const t_hashmap *map, const char *key)
{
	t_node	*entry;

	if (map->buckets.cap == 0)
		return (NULL);
	entry = ((t_list *)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return (((t_key_value *)entry->content)->value);
		entry = entry->next;
	}
	return (NULL);
}

const void	*hashmap_get_const(const t_hashmap *map, const char *key)
{
	return (hashmap_get(map, key));
}

const t_key_value	**hashmap_get_all(const t_hashmap *map)
{
	const t_key_value	**res;
	size_t				pair_i;
	t_node				*entry;
	size_t				bucket_i;

	res = malloc(sizeof(t_key_value *) * (map->size + 1));
	if (res == NULL)
		return (NULL);
	bucket_i = 0;
	pair_i = 0;
	while (bucket_i < map->buckets.len)
	{
		entry = ((t_list *)map->buckets.data)[bucket_i];
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

	if (map->buckets.cap == 0)
		return (false);
	bucket_i = map->hash(key) % map->buckets.cap;
	bucket = ((t_list *)map->buckets.data)[bucket_i];
	entry = bucket;
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
		{
			pair = entry->content;
			entry->content = NULL;
			list_rm(&bucket, entry, NULL);
			key_value_free(&pair, map->del_value);
			((t_list *)map->buckets.data)[bucket_i] = bucket;
			map->size--;
			return (true);
		}
		entry = entry->next;
	}
	return (false);
}

bool	hashmap_contains(const t_hashmap *map, const char *key)
{
	t_node	*entry;

	if (map->buckets.cap == 0)
		return (NULL);
	entry = ((t_list *)map->buckets.data)[map->hash(key) % map->buckets.cap];
	while (entry != NULL)
	{
		if (is_matching_key(entry->content, key))
			return (true);
		entry = entry->next;
	}
	return (false);
}
