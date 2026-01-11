/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:13:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 05:50:55 by gastesan         ###   ########.fr       */
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

#endif
