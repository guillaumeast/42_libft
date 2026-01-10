/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:31:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STASH_H
# define STASH_H

# include "libft.h"

/**
 * @struct s_stash
 * @brief Structure for storing file descriptor and its associated buffer.
 *
 * @var s_stash::fd File descriptor.
 * @var s_stash::buffer Buffer for storing read data.
 */
typedef struct s_stash
{
	int			fd;
	t_buff		buffer;
}	t_stash;

/**
 * @brief Gets or creates a buffer for a file descriptor.
 *
 * @param fd File descriptor.
 * @return Pointer to the buffer, or NULL on failure.
 */
t_buff	*get_buffer(int fd);

/**
 * @brief Finds and frees the stash for a file descriptor.
 *
 * @param fd File descriptor.
 */
void	stash_find_and_free(int fd);

/**
 * @brief Frees all stashs and their buffers.
 */
void	stashs_free_all(void);

#endif
