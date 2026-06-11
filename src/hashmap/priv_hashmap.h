/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priv_hashmap.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:36:16 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:24:59 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIV_HASHMAP_H
# define PRIV_HASHMAP_H

#include "libft.h"

/**
 * @brief Default string hash function (djb2).
 *
 * Computes a hash over the bytes of a NUL-terminated key. The returned value
 * is reduced modulo the bucket count by the caller.
 *
 * @param key NUL-terminated key to hash (borrowed).
 * @return The computed hash value.
 */
size_t		hash_string(char *key);

/**
 * @brief Doubles the bucket capacity and rehashes every stored pair.
 *
 * Allocates a new bucket array of twice the current capacity, swaps it in and
 * redistributes the existing pairs into it. The pairs themselves are moved,
 * not reallocated. On failure the previous bucket array is restored, leaving
 * the map unchanged.
 *
 * @note Pairs are transferred between bucket arrays; their keys and values are
 *       never freed by a successful resize.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @return true on success, false on memory allocation failure.
 */
bool		hashmap_resize(t_hashmap *map);

/**
 * @brief Inserts a pair into the map, or replaces an existing one.
 *
 * Appends new to its target bucket chain. If a pair with the same key already
 * exists in that bucket, its value is released through the map's del callback
 * and the existing entry adopts new (see bucket_replace), in which case size
 * is left unchanged.
 *
 * @note On success the map takes ownership of new. On failure new is left
 *       untouched and ownership remains with the caller.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param new Pair to insert (ownership transferred on success).
 * @return true on success, false on memory allocation failure.
 */
bool		hashmap_insert(t_hashmap *map, t_key_value *new);

#endif
