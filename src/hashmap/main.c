/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 16:52:01 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/09 13:56:34 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#define HASHMAP_INIT_CAP	50

typedef t_vector	t_buckets;
typedef t_list		t_entries;

typedef struct s_entry
{
	char	*key;
	void	*value;
}	t_entry;

typedef struct s_hashmap
{
	size_t		size;
	t_buckets	buckets;
	size_t		(*hash)(char *key);
	void 		(*del_value)(void *);
}	t_hashmap;

void	*hashmap_get(t_hashmap *map, char *key);
bool	hashmap_remove(t_hashmap *map, char *key);
bool	hashmap_contains(t_hashmap *map, char *key);
bool	hashmap_put(t_hashmap *map, char *key, void *value);

// ---------- entries ----------

// --- entries init ---

t_entry	*entry_new(char *key, void *value)
{
	t_entry	*entry;

	entry = malloc(sizeof(t_entry));
	if (entry == NULL)
		return (NULL);
	entry->key = str_dup(key);
	if (entry->key == NULL)
		return (free(entry), NULL);
	entry->value = value;
	return (entry);
}

void	entry_free(t_entry *entry, void (*del_value)(void *))
{
	if (del_value)
		del_value(entry->value);
	free(entry->key);
	*entry = (t_entry){0};
	free(entry);
}

// ---------- buckets ----------

// --- buckets init ---

bool	buckets_init(t_buckets *buckets, size_t init_cap)
{
	size_t	i;

	if (!vector_init(buckets, sizeof(t_list), init_cap))
		return (false);
	i = 0;
	while (i < init_cap)
		((t_list *)buckets->data)[i++] = NULL;
	return (true);
}

void	buckets_clean(t_buckets *buckets, void (*del_value)(void *))
{
	t_entries	bucket;
	size_t		entry_i;
	size_t		bucket_i;

	bucket_i = 0;
	while (bucket_i < buckets->len)
	{
		bucket = ((t_list *)buckets->data)[bucket_i];
		if (bucket != NULL)
		{
			entry_i = 0;
			while (list_get_content_n(bucket, entry_i) != NULL)
				entry_free(list_get_content_n(bucket, entry_i++), del_value);
			list_rm_all(((t_list *)buckets->data) + bucket_i, NULL);
			((t_list *)buckets->data)[bucket_i] = NULL;
		}
		bucket_i++;
	}
}

void	buckets_free(t_buckets *buckets, void (*del_value)(void *))
{
	buckets_clean(buckets, del_value);
	vector_free(buckets, NULL);
}

// ---------- hashmap ----------

// --- hashmap utils ---

size_t	hash_string(char *key)
{
	size_t	i;
	size_t	hash;

	i = 0;
	hash = 5381;
	while (key[i] != '\0')
		hash = ((hash << 5) + hash) + (unsigned char)key[i++];
	return (hash);
}

bool	hashmap_replace(t_hashmap *map, t_entries bucket, t_entry *new)
{
	t_entry		*entry;
	size_t		entry_i;

	entry_i = 0;
	while (list_get_content_n(bucket, entry_i) != NULL)
	{
		entry = list_get_content_n(bucket, entry_i);
		if (str_ncmp(entry->key, new->key, str_len(new->key) + 1) == 0)
		{
			if (map->del_value)
				map->del_value(entry->value);
			entry->value = new->value;
			return (true);
		}
		entry_i++;
	}
	return (false);
}

bool	hashmap_place(t_hashmap *map, t_buckets *buckets, t_entry *new)
{
	t_entries	bucket;
	size_t		bucket_i;

	if (new == NULL)
		return (false);
	bucket_i = map->hash(new->key) % buckets->cap;
	bucket = ((t_list *)buckets->data)[bucket_i];
	if (bucket != NULL && hashmap_replace(map, bucket, new))
		return (entry_free(new, NULL), true);
	if (!list_add_end(&bucket, new))
		return (false);
	if (buckets->len <= bucket_i)
		buckets->len = bucket_i + 1;
	map->size++;
	((t_list *)buckets->data)[bucket_i] = bucket;
	return (true);
}

static bool	hashmap_redistribute(t_hashmap *map, t_buckets *new_buckets)
{
	t_entry		*entry;
	t_entries	entries;
	size_t		entry_i;
	size_t		bucket_i;
	t_node 		*entry_node;

	bucket_i = 0;
	while (bucket_i < map->buckets.len)
	{
		entries = ((t_list *)map->buckets.data)[bucket_i];
		if (entries != NULL)
		{
			entry_i = 0;
			while (list_get_node_n(entries, entry_i) != NULL)
			{
				entry_node = list_get_node_n(entries, entry_i);
				entry = ((t_entry *)entry_node->content);
				if (entry == NULL)
					return (false);
				entry_node->content = NULL;
				if (!hashmap_place(map, new_buckets, entry))
					return (entry_node->content = entry, false);
				entry_i++;
			}
		}
		bucket_i++;
	}
	return (true);
}

bool	hashmap_resize(t_hashmap *map)
{
	size_t		prev_size;
	t_buckets 	new_buckets;
	
	if (!buckets_init(&new_buckets, map->buckets.cap * 2))
		return (false);
	prev_size = map->size;
	map->size = 0;
	if (!hashmap_redistribute(map, &new_buckets))
	{
		map->size = prev_size - map->size;
		return (buckets_free(&new_buckets, map->del_value), false);
	}
	buckets_free(&map->buckets, map->del_value);
	map->buckets = new_buckets;
	return (true);
}

// --- hashmap init ---

bool	hashmap_init(t_hashmap *map, void (*del_value)(void *))
{
	*map = (t_hashmap){0};
	if (!buckets_init(&map->buckets, HASHMAP_INIT_CAP))
		return (false);
	map->hash = hash_string;
	map->del_value = del_value;
	return (true);
}

void	hashmap_clean(t_hashmap *map)
{
	buckets_clean(&map->buckets, map->del_value);
	map->size = 0;
}

void	hashmap_free(t_hashmap *map)
{
	buckets_free(&map->buckets, map->del_value);
	*map = (t_hashmap){0};
}

// --- hashmap API ---

bool	hashmap_put(t_hashmap *map, char *key, void *value)
{
	t_entry	*entry;

	if (map->size + 1 > map->buckets.cap && !hashmap_resize(map))
		return (false);
	entry = entry_new(key, value);
	if (entry == NULL)
		return (false);
	if (!hashmap_place(map, &map->buckets, entry))
		return (entry_free(entry, map->del_value), false);
	return (true);
}

void	*hashmap_get(t_hashmap *map, char *key)
{
	t_entries	bucket;
	t_entry		*entry;
	size_t		entry_i;
	size_t		bucket_i;

	bucket_i = map->hash(key) % map->buckets.cap;
	bucket = ((t_list *)map->buckets.data)[bucket_i];
	if (bucket == NULL)
		return (NULL);
	entry_i = 0;
	while (list_get_content_n(bucket, entry_i) != NULL)
	{
		entry = list_get_content_n(bucket, entry_i);
		if (str_ncmp(entry->key, key, str_len(key) + 1) == 0)
			return (entry->value);
		entry_i++;
	}
	return (NULL);
}

bool	hashmap_remove(t_hashmap *map, char *key)
{
	t_entries	bucket;
	size_t		node_i;
	t_entry		*entry;
	size_t		bucket_i;
	t_node		*entry_node;

	bucket_i = map->hash(key) % map->buckets.cap;
	bucket = ((t_list *)map->buckets.data)[bucket_i];
	if (bucket == NULL)
		return (false);
	node_i = 0;
	while (list_get_node_n(bucket, node_i) != NULL)
	{
		entry_node = list_get_node_n(bucket, node_i);
		entry = entry_node->content;
		if (str_ncmp(entry->key, key, str_len(key) + 1) == 0)
		{
			entry_free(entry, map->del_value);
			list_rm(&bucket, entry_node, NULL);
			((t_list *)map->buckets.data)[bucket_i] = bucket;
			return (map->size--, true);
		}
		node_i++;
	}
	return (false);
}

bool	hashmap_contains(t_hashmap *map, char *key)
{
	t_entries	bucket;
	t_entry		*entry;
	size_t		entry_i;
	size_t		bucket_i;

	bucket_i = map->hash(key) % map->buckets.cap;
	bucket = ((t_list *)map->buckets.data)[bucket_i];
	if (bucket == NULL)
		return (false);
	entry_i = 0;
	while (list_get_content_n(bucket, entry_i) != NULL)
	{
		entry = list_get_content_n(bucket, entry_i);
		if (str_ncmp(entry->key, key, str_len(key) + 1) == 0)
			return (true);
		entry_i++;
	}
	return (false);
}
