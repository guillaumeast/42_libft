/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:26 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 02:56:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_stash	*stash_new(int fd);

t_buff	*get_buffer(t_list *stashs, int fd)
{
	t_node	*node;
	t_stash	*stash;
	t_stash	*new_stash;

	node = *stashs;
	while (node)
	{
		stash = node->content;
		if (stash->fd == fd)
			return (&stash->buffer);
		node = node->next;
	}
	new_stash = stash_new(fd);
	if (!new_stash)
		return (NULL);
	if (!list_add_end(stashs, new_stash))
	{
		buff_free(&new_stash->buffer);
		free(new_stash);
		return (NULL);
	}
	return (&new_stash->buffer);
}

static t_stash	*stash_new(int fd)
{
	t_stash	*new_stash;

	new_stash = malloc(sizeof *new_stash);
	if (!new_stash)
		return (NULL);
	new_stash->fd = fd;
	if (!buff_init(&new_stash->buffer, BUFFER_SIZE))
	{
		free(new_stash);	
		return (NULL);
	}
	ft_bzero(new_stash->buffer.data, new_stash->buffer.cap);
	return (new_stash);
}

void	stash_remove(t_list *stashs, int fd)
{
	t_node	*node;
	t_stash	*stash;

	if (!stashs || !*stashs)
		return ;
	node = *stashs;
	while (node)
	{
		stash = node->content;
		if (stash->fd == fd)
		{
			buff_free(&stash->buffer);
			free(stash);
			list_rm(stashs, node, NULL);
			break ;
		}
		node = node->next;
	}
}
