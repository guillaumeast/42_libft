/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 02:13:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 02:13:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFF_INTERNAL_H
# define BUFF_INTERNAL_H

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

#endif
