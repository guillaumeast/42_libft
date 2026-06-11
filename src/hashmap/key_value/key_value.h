/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:24:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:24:51 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_VALUE_H
# define KEY_VALUE_H

# include "libft.h"

/**
 * @brief Allocates a key/value pair.
 *
 * Duplicates key into a private buffer and stores value by reference. The
 * caller therefore keeps ownership of the key buffer, while the new pair takes
 * ownership of value.
 *
 * @note On success, ownership of value is transferred to the pair. On failure,
 *       value is not retained and the caller keeps its ownership.
 *
 * @param key NUL-terminated key to copy (borrowed; duplicated internally).
 * @param value Value to store (ownership transferred on success).
 * @return Pointer to the new pair (owned by caller), or NULL on allocation
 *         failure.
 */
t_key_value	*key_value_new(char *key, void *value);

/**
 * @brief Frees a key/value pair and its contents.
 *
 * Frees the duplicated key, passes the value to del (if provided) and frees
 * the pair itself. The caller's pointer is set to NULL. Safe to call with a
 * NULL pair pointer or a NULL pair.
 *
 * @param pair Address of the pair pointer to free (set to NULL on return).
 * @param del Optional destructor applied to the stored value (may be NULL).
 */
void		key_value_free(t_key_value **pair, void (*del)(void *));

/**
 * @brief Tests whether a pair's key equals the given key.
 *
 * @warning pair and pair->key must not be NULL.
 *
 * @param pair Pair whose key is compared (borrowed).
 * @param key NUL-terminated key to compare against (borrowed).
 * @return true if the keys are equal, false otherwise.
 */
bool		is_matching_key(t_key_value *pair, char *key);

#endif
