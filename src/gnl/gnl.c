/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 23:31:54 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/09 21:17:54 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static t_buff	*get_buffer(t_list *stashs, int fd);
static t_stash	*stash_new(int fd);

char	*get_next_line(int fd)
{
	static t_list	stashs;
	t_buff			*buffer;
	t_buff			line;
	bool			success;

	if (fd < 0)
		return (NULL);
	buffer = get_buffer(&stashs, fd);
	if (!buffer)
		return (NULL);
	buff_init(&line, 0);
	success = parse_line(fd, buffer, &line);
	if (success && line.cap > line.len + 1)
		line_realloc(&line, line.len + 1);
	if (!success)
	{
		free(line.data);
		line.data = NULL;
	}
	if (!success || buffer->len == 0)
		stash_remove(&stashs_head, fd);
	return (line.data);
}

static t_buff	*get_buffer(t_list *stashs, int fd)
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
		if (!node->next)
			break ;
		node = node->next;
	}
	new_stash = stash_new(fd);
	if (!new_stash)
		return (NULL);
	// TODO: add new stach to list
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

static void	stash_remove(t_stash **stashs_head, int fd)
{
	t_stash	*stash;
	t_stash	*next;

	if (!stashs_head || !*stashs_head)
		return ;
	if ((*stashs_head)->fd == fd)
	{
		next = (*stashs_head)->next;
		free(*stashs_head);
		(*stashs_head) = next;
		return ;
	}
	stash = (*stashs_head);
	while (stash->next)
	{
		next = stash->next;
		if (next->fd == fd)
			break ;
		stash = next;
	}
	if (!next || next->fd != fd)
		return ;
	stash->next = next->next;
	free(next);
}

static bool	parse_line(int fd, t_buffer *buffer, t_line *line)
{
	ssize_t	nl_index;

	if (buffer->len <= 0)
		buffer->len = read(fd, buffer->data, BUFFER_SIZE);
	while (buffer->len > 0)
	{
		nl_index = get_index_n(buffer->data, '\n', (size_t)buffer->len);
		if (nl_index >= 0)
		{
			line_add(line, buffer, (size_t)(nl_index + 1));
			if (!line->data)
				return (false);
			buffer_move(buffer, (size_t)(nl_index + 1));
			return (true);
		}
		line_add(line, buffer, (size_t)buffer->len);
		if (!line->data)
			return (false);
		buffer_reset(buffer);
		buffer->len = read(fd, buffer->data, BUFFER_SIZE);
	}
	if (buffer->len < 0)
		return (false);
	return (true);
}
