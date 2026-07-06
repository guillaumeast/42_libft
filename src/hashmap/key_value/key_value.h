/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_value.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 16:24:06 by adouieb           #+#    #+#             */
/*   Updated: 2026/07/06 15:18:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_VALUE_H
# define KEY_VALUE_H

# include "libft.h"

/**
 * @brief Tests whether a pair's key equals the given key.
 *
 * @warning pair and pair->key must not be NULL.
 *
 * @param pair Pair whose key is compared (borrowed).
 * @param key NUL-terminated key to compare against (borrowed).
 * @return true if the keys are equal, false otherwise.
 */
bool		is_matching_key(t_key_value *pair, const char *key);

#endif
