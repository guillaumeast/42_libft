/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:13:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:19:50 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFF_INTERNAL_H
# define BUFF_INTERNAL_H

# include "libft.h"
# include <stddef.h>

/**
 * @brief Calculates the required capacity to accommodate a target length.
 *
 * Uses exponential growth strategy (doubles capacity) to amortize
 * multiple growth operations to O(1) on average.
 *
 * @param current_cap Current capacity of the buffer.
 * @param target_len Target length to accommodate.
 * @return The new required capacity.
 */
size_t	buff_get_required_cap(size_t current_cap, size_t target_len);

/**
 * @brief Grows the buffer to accommodate the target length if necessary.
 *
 * No-op if current capacity is already sufficient.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param target_len The minimum length the buffer should accommodate.
 * @return true on success, false on memory allocation failure.
 */
bool	buff_grow(t_buff *buff, size_t target_len);

/**
 * @brief Reads up to n bytes from a file descriptor into a buffer.
 *
 * Reads directly at the end of buff->data and increases buff->len by the
 * number of bytes read. Reading stops after n bytes, EOF, or a read error.
 *
 * @note Interrupted reads (EINTR) are retried.
 *
 * @warning buff must be initialized before calling this function.
 * @warning buff must have enough available capacity for n additional bytes.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @param n Maximum number of bytes to read.
 * @return Number of bytes read, or -1 on read error.
 */
ssize_t	buff_read_n_bytes(t_buff *buff, int fd, size_t n);

#endif
