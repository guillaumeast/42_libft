/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:15:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

#define DEFAULT_BUFF_CAP 128
#define BUFF_GROWTH 2

/**
 * @brief Initializes a buffer with the specified initial capacity.
 *
 * @note Cannot fail when initial_cap == 0.
 *
 * @param b Pointer to the buffer structure.
 * @param initial_cap Initial capacity of the buffer.
 * @return true on success, false on memory allocation failure.
 */
bool	buff_init(t_buff *b, size_t initial_cap)
{
	b->data = NULL;
	b->cap = 0;
	b->len = 0;
	if (initial_cap == 0)
		return (true);
	b->data = malloc(initial_cap);
	if (!b->data)
		return (false);
	b->cap = initial_cap;
	return (true);
}

// TODO: expliciter que la capacity est multipliée si insuffisante pour amortir les growth en 0(1)
/**
 * @brief Calculates the required capacity to accommodate a target length.
 *
 * @param current_cap Current capacity of the buffer.
 * @param target_len Target length to accommodate.
 * @return The new required capacity.
 */
size_t	buff_get_required_cap(size_t current_cap, size_t target_len)
{
	size_t	new_cap;

	if (target_len == 0)
		return (current_cap);
	if (current_cap == 0)
		new_cap = DEFAULT_BUFF_CAP;
	else
		new_cap = current_cap;
	while (new_cap <= target_len)
		new_cap *= BUFF_GROWTH;
	return (new_cap);
}

// TODO: expliciter que le grow n'est effectué que si nécessaire (si la capcity est déjà suffisante -> no-op)
/**
 * @brief Grows the buffer to accommodate the target length.
 *
 * @param buff Pointer to the buffer.
 * @param target_len The minimum length the buffer should accommodate.
 * @return true on success, false on memory allocation failure.
 */
bool	buff_grow(t_buff *buff, size_t target_len)
{
	size_t	new_cap;
	char	*new_data;

	new_cap = buff_get_required_cap(buff->cap, target_len);
	if (new_cap == buff->cap)
		return (true);
	new_data = malloc(new_cap);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = new_cap;
	return (true);
}

/**
 * @brief Adjusts buffer capacity to match its current length.
 *
 * @param buff Pointer to the buffer.
 * @return true on success, false on memory allocation failure.
 */
bool	buff_adjust(t_buff *buff)
{
	char	*new_data;

	if (buff->len == 0)
	{
		if (buff->data)
			free(buff->data);
		buff->data = NULL;
		buff->cap = 0;
		return (true);
	}
	new_data = malloc(buff->len);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = buff->len;
	return (true);
}

// TODO: expliciter le fait que c'est le char * interne au buffer qui est free, pas le t_buff lui-même
/**
 * @brief Frees the buffer's allocated memory.
 *
 * @param b Pointer to the buffer.
 */
void	buff_free(t_buff *b)
{
	if (b->data)
		free(b->data);
	b->data = NULL;
}
