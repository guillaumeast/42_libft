/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buckets.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:22:55 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/28 14:40:02 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUCKETS_H
# define BUCKETS_H

# include "libft.h"

/**
 * @brief Initializes the bucket array.
 *
 * Allocates a vector of init_cap t_list slots and zeroes it, so every bucket
 * starts as an empty (NULL) chain.
 *
 * @param buckets Pointer to the vector to initialize (uninitialized).
 * @param init_cap Number of buckets to allocate.
 * @return true on success, false on memory allocation failure.
 */
bool	buckets_init(t_vector *buckets, size_t init_cap);

/**
 * @brief Frees the bucket array and every pair it contains.
 *
 * Frees each bucket chain (every pair's key and, through del, its value) and
 * then frees the underlying vector. The vector is left in a freed state.
 *
 * @param buckets Pointer to the bucket vector to free (borrowed).
 * @param del Optional destructor applied to each stored value (may be NULL).
 */
void	buckets_free(t_vector *buckets, void (*del)(void *));

/**
 * @brief Detaches every pair from the bucket chains without freeing them.
 *
 * Sets each list node's content to NULL across all buckets, severing the link
 * between the chains and their pairs. Used during a resize so the old chains
 * can be freed while the pairs themselves are kept (they have been moved into
 * the new bucket array).
 *
 * @param buckets Pointer to the bucket vector to detach (borrowed).
 */
void	buckets_detach(t_vector *buckets);

/**
 * @brief Swaps the contents of two bucket vectors.
 *
 * Exchanges the two t_vector structures by value; no allocation occurs and no
 * pair is moved in memory.
 *
 * @param buckets1 First bucket vector (borrowed).
 * @param buckets2 Second bucket vector (borrowed).
 */
void	buckets_swap(t_vector *buckets1, t_vector *buckets2);

/**
 * @brief Applies a function to every used bucket slot.
 *
 * Iterates over the first vector->len slots and calls f with the address of
 * each bucket slot and the del callback, allowing f to free or mutate the
 * chain stored there.
 *
 * @param vector Pointer to the bucket vector to iterate (borrowed).
 * @param del Destructor forwarded to f for each slot (may be NULL).
 * @param f Function applied to each bucket slot (borrowed).
 */
void	buckets_foreach(t_vector *vector, void (*del)(void *),
			void (*f)(void *, void (*del)(void *)));

/**
 * @brief Frees a single bucket chain and its pairs.
 *
 * Frees every pair in the chain (key and, through del, value) and removes all
 * list nodes. Shaped to be used as a buckets_foreach() callback.
 *
 * @param bucket_ptr Address of the bucket slot (a t_list *) to free (borrowed).
 * @param del Optional destructor applied to each stored value (may be NULL).
 */
void	bucket_free(void *bucket_ptr, void (*del)(void *));

/**
 * @brief Tests whether a bucket chain holds a pair with the given key.
 *
 * @param bucket Head of the bucket chain to search (borrowed, may be NULL).
 * @param key NUL-terminated key to look for (borrowed).
 * @return true if a matching pair is found, false otherwise.
 */
bool	bucket_contains(t_list bucket, const char *key);

/**
 * @brief Detaches every pair from a single bucket chain without freeing them.
 *
 * Sets each node's content to NULL. Shaped to be used as a buckets_foreach()
 * callback; the destructor parameter is unused.
 *
 * @param bucket Address of the bucket slot (a t_list *) to detach (borrowed).
 * @param _ Unused destructor parameter (required by the callback signature).
 */
void	bucket_detach(void *bucket, void (*_)(void *));

/**
 * @brief Replaces the value of the pair matching new->key within a chain.
 *
 * Walks the chain and, for the node whose key matches new->key, releases the
 * existing pair (its value through del) and stores new in its place.
 *
 * @note Ownership of new is transferred to the matching node. The previously
 *       stored pair is freed.
 *
 * @param bucket Head of the bucket chain to update (borrowed).
 * @param new Replacement pair carrying the matching key (ownership
 *            transferred).
 * @param del Optional destructor applied to the replaced value (may be NULL).
 */
void	bucket_replace(t_list bucket, t_key_value *new, void (*del)(void *));
#endif
