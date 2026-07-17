/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:13:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/17 15:36:57 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_INTERNAL_H
# define STRING_INTERNAL_H

# include "libft.h"
# include <stddef.h>

/**
 * @brief Calculates the required capacity to accommodate a target cap.
 *
 * Uses exponential growth strategy (doubles capacity) to amortize
 * multiple growth operations to O(1) on average.
 *
 * @param current_cap Current capacity of the string.
 * @param target_len Target length to accommodate.
 * @return The new required capacity.
 */
size_t	string_get_required_cap(size_t current_cap, size_t target_cap);

/**
 * @brief Reads up to n bytes from a file descriptor into a string.
 *
 * Reads directly at the end of string->data and increases string->len by the
 * number of bytes read. Reading stops after n bytes, EOF, or a read error.
 *
 * @note Interrupted reads (EINTR) are retried.
 *
 * @warning string must be initialized before calling this function.
 * @warning string must have enough available capacity for n additional bytes.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fd File descriptor to read from.
 * @param n Maximum number of bytes to read.
 * @return Number of bytes read, or -1 on read error.
 */
ssize_t	string_read_n_bytes(t_string *string, int fd, size_t n);

#endif
