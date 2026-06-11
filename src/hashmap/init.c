/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:30:50 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 17:50:06 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include "buckets.h"
#include "priv_hashmap.h"

bool	hashmap_init(t_hashmap *map, size_t initial_cap, void (*del)(void *))
{
	*map = (t_hashmap){0};
	if (!buckets_init(&map->buckets, initial_cap))
		return (false);
	map->hash = hash_string;
	map->del_value = del;
	return (true);
}

void	hashmap_free(t_hashmap *map)
{
	buckets_free(&map->buckets, map->del_value);
	*map = (t_hashmap){0};
}
