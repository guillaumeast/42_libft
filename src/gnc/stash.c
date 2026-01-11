/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:14 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 03:20:18 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stash.h"
#include <stdlib.h>

static t_list	g_stashs = NULL;

t_buff	*get_buffer(int fd)
{
	t_node	*node;
	t_stash	*stash;
	t_stash	*new_stash;

	node = g_stashs;
	while (node)
	{
		stash = node->content;
		if (stash->fd == fd)
			return (&stash->buffer);
		node = node->next;
	}
	new_stash = malloc(sizeof * new_stash);
	if (!new_stash)
		return (NULL);
	new_stash->fd = fd;
	buff_init(&new_stash->buffer, 0);
	if (!list_add_end(&g_stashs, new_stash))
	{
		buff_free(&new_stash->buffer);
		free(new_stash);
		return (NULL);
	}
	return (&new_stash->buffer);
}

/**
 * @brief Frees a stash structure and its buffer.
 *
 * @param stash_ptr Pointer to the stash.
 */
void	stash_free(void *stash_ptr)
{
	t_stash	*stash;

	stash = stash_ptr;
	buff_free(&stash->buffer);
	free(stash);
}

void	stash_find_and_free(int fd)
{
	t_node	*node;
	t_stash	*stash;

	if (!g_stashs)
		return ;
	node = g_stashs;
	while (node)
	{
		stash = node->content;
		if (stash->fd == fd)
		{
			list_rm(&g_stashs, node, stash_free);
			break ;
		}
		node = node->next;
	}
}

void	stashs_free_all(void)
{
	if (!g_stashs)
		return ;
	list_rm_all(&g_stashs, stash_free);
}
