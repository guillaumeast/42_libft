/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_ops.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:18:17 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

// TODO: préciser que le buffer est automatiquement aggrandi si nécessaire
/**
 * @brief Prepends a string to the beginning of the buffer.
 *
 * @param b Pointer to the buffer.
 * @param str String to prepend.
 * @param n Number of bytes to prepend, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_prepend(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		b->cap = new_cap;
		ft_memcpy(new_data + strlen, b->data, b->len);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + strlen, b->data, b->len);
	ft_memcpy(b->data, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

// TODO: préciser que le buffer est automatiquement aggrandi si nécessaire
/**
 * @brief Inserts a string at a specific index in the buffer.
 *
 * @param b Pointer to the buffer.
 * @param index Position at which to insert the string.
 * @param str String to insert.
 * @param n Number of bytes to insert, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_insert(t_buff *b, size_t index, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;
	size_t	new_cap;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		new_data = malloc(new_cap);
		if (!new_data)
			return (false);
		b->cap = new_cap;
		ft_memcpy(new_data, b->data, index);
		ft_memcpy(new_data + index + strlen, b->data + index, b->len - index);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + index + strlen, b->data + index, b->len - index);
	ft_memcpy(b->data + index, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

// TODO: préciser que le buffer est automatiquement aggrandi si nécessaire
/**
 * @brief Appends a string to the end of the buffer.
 *
 * @param b Pointer to the buffer.
 * @param str String to append.
 * @param n Number of bytes to append, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 */
bool	buff_append(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	size_t	new_cap;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	new_cap = buff_get_required_cap(b->cap, b->len + strlen);
	if (new_cap > b->cap)
	{
		if (!ft_realloc(&b->data, b->cap, new_cap))
			return (false);
		b->cap = new_cap;
	}
	ft_memcpy(b->data + b->len, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

// TODO: préciser que c'est au caller de free le buffer qui est retourné
/**
 * @brief Duplicates up to n bytes of a buffer into a new buffer.
 *
 * @param src Source buffer to duplicate.
 * @param n Maximum number of bytes to copy.
 * @return Pointer to the new buffer, or NULL on failure.
 */
t_buff	*buff_dup_n(const t_buff *src, size_t n)
{
	t_buff	*res;

	res = malloc(sizeof * res);
	if (!res)
		return (NULL);
	if (n > src->len)
		n = src->len;
	buff_init(res, 0);
	if (!buff_append(res, src->data, (long)n))
	{
		buff_free(res);
		free(res);
		return (NULL);
	}
	return (res);
}

/**
 * @brief Removes a portion of the buffer starting at i_start.
 *
 * @note If len < 0, deletes all buffer content from i_start.
 *
 * @param buff Pointer to the buffer.
 * @param i_start Starting index for removal.
 * @param len Number of bytes to remove, or negative to remove until end.
 */
void	buff_rm_part(t_buff *buff, size_t i_start, ssize_t len)
{
	char	*dst;
	char	*src;
	size_t	len_to_move;

	if (i_start >= buff->len)
		return ;
	else if (len < 0 || i_start + (size_t)len > buff->len)
	{
		buff->len = i_start;
		return ;
	}
	dst = buff->data + i_start;
	src = buff->data + i_start + (size_t)len;
	len_to_move = buff->len - (i_start + (size_t)len);
	ft_memmove(dst, src, len_to_move);
	buff->len -= (size_t)len;
}
