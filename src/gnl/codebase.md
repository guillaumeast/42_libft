tree
```bash
gnl
├── get_next_line.h
├── gnl.c
└── stash.c

1 directory, 3 files
```

./get_next_line.h
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:59:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 02:49:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

t_buff	*get_buffer(t_list *stashs, int fd);
void	stash_remove(t_list *stashs, int fd);

#endif

```

./gnl.c
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:22 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 03:13:56 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

static bool		parse_line(int fd, t_buff *b, t_buff *line);
static ssize_t	get_index_n(const char *buff, char c, size_t n);
static void		buff_move(t_buff *buffer, size_t index);
static bool		line_realloc(t_buff *line, size_t cap);

char	*gnl(int fd)
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
	if (!buff_init(&line, 0))
		return (NULL);
	success = parse_line(fd, buffer, &line);
	if (success && line.cap > line.len + 1)
		line_realloc(&line, line.len + 1);
	if (!success)
	{
		free(line.data);
		line.data = NULL;
	}
	if (!success || buffer->len == 0)
		stash_remove(&stashs, fd);
	return (line.data);
}

static bool	parse_line(int fd, t_buff *buffer, t_buff *line)
{
	ssize_t	nl_index;
	ssize_t	bytes;

	while (true)
	{
		bytes = read(fd, buffer->data + buffer->len, buffer->cap - buffer->len);
		if (bytes == 0 || (bytes == -1 && errno != EINTR))
			break ;
		else if (bytes == -1 && errno == EINTR)
			continue ;
		buffer->len += (size_t)bytes;
		nl_index = get_index_n(buffer->data, '\n', (size_t)buffer->len);
		if (nl_index >= 0)
		{
			if (!buff_append(line, buffer->data, nl_index + 1))
				return (false);
			buff_move(buffer, (size_t)nl_index + 1);
			return (true);
		}
		if (!buff_append(line, buffer->data, (long)buffer->len))
			return (false);
		ft_bzero(buffer->data, buffer->len);
		buffer->len = 0;
	}
	return (bytes >= 0);
}

static ssize_t	get_index_n(const char *buff, char c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (buff[i] == c)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}

static void	buff_move(t_buff *buffer, size_t index)
{
	ft_memmove(buffer->data, buffer->data + index, buffer->len - index);
	ft_bzero(buffer->data + index, buffer->len - index);
	buffer->len = buffer->len - index;
}

static bool	line_realloc(t_buff *line, size_t cap)
{
	char	*old_data;
	char	*new_data;
	size_t	len_to_copy;
	size_t	i;

	old_data = line->data;
	new_data = malloc(cap);
	if (!new_data)
		return (false);
	if (line->len < cap)
		len_to_copy = line->len;
	else
		len_to_copy = cap;
	i = 0;
	while (i < len_to_copy)
	{
		new_data[i] = line->data[i];
		i++;
	}
	new_data[i] = '\0';
	free(old_data);
	line->data = new_data;
	line->len = len_to_copy;
	line->cap = cap;
	return (true);
}

```

./stash.c
```c
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

```

