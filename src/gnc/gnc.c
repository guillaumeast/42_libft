/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:29:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stash.h"
#include <stdlib.h>

static int		read_until_sep(t_buff *buff, int fd, char separator);
static t_buff	*get_chunk(t_buff *buff, int sep_index);

// TODO: préciser que la fonction renvoie le chunk si EOF avant que le separator soit trouvé (elle ne renvoie NULL que lorsqu'elle est appellée alors qu'on a déjà atteint EOF !)
/**
 * @brief Reads the next chunk from a file descriptor until separator is found.
 *
 * @param fd File descriptor to read from.
 * @param separator Character to stop reading at.
 * @return Pointer to a new buffer containing the chunk, or NULL on error/EOF.
 */
t_buff	*get_next_chunk(int fd, char separator)
{
	t_buff			*buff;
	int				sep_index;
	t_buff			*chunk;

	if (fd < 0)
		return (NULL);
	buff = get_buffer(fd);
	if (!buff)
		return (NULL);
	sep_index = read_until_sep(buff, fd, separator);
	if (sep_index == -2)
		return (stash_find_and_free(fd), NULL);
	chunk = get_chunk(buff, sep_index);
	if (!chunk)
		return (stash_find_and_free(fd), NULL);
	if (buff->len == 0)
		stash_find_and_free(fd);
	buff_adjust(chunk);
	return (chunk);
}

/**
 * @brief Reads from file descriptor until separator is found.
 *
 * @param buff Pointer to the buffer.
 * @param fd File descriptor.
 * @param separator Character to search for.
 * @return Index of separator (>=0), -1 if not found, -2 on error.
 */
static int	read_until_sep(t_buff *buff, int fd, char separator)
{
	int	sep_index;

	sep_index = buff_get_index(buff, separator);
	if (sep_index == -1)
		sep_index = buff_read_until(buff, fd, separator);
	return (sep_index);
}

// TODO: préciser que -1 est pour extraire tout le contenu du buffer
/**
 * @brief Extracts a chunk from the buffer up to the separator index.
 *
 * @param buff Source buffer.
 * @param sep_index Index of the separator (-1 if not found).
 * @return Pointer to the new chunk buffer, or NULL on failure.
 */
static t_buff	*get_chunk(t_buff *buff, int sep_index)
{
	size_t	chunk_len;
	t_buff	*chunk;

	if (buff->len == 0)
		return (NULL);
	if (sep_index == -1)
		chunk_len = buff->len;
	else
		chunk_len = (size_t)sep_index + 1;
	chunk = buff_dup_n(buff, chunk_len);
	if (!chunk)
		return (NULL);
	buff_adjust(chunk);
	buff_rm_part(buff, 0, (ssize_t)chunk_len);
	return (chunk);
}

/**
 * @brief Frees all stashed buffers used by get_next_chunk.
 */
void	get_next_chunk_free(void)
{
	stashs_free_all();
}
