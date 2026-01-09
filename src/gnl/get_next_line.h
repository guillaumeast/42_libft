/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 22:59:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/09 21:10:21 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>



typedef struct s_line
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_line;

typedef struct s_buffer
{
	char	data[BUFFER_SIZE];
	ssize_t	len;
}	t_buffer;



char	*get_next_line(int fd);
ssize_t	get_index_n(const char *buff, char c, size_t n);
bool	line_add(t_line *dst, const t_buffer *src, size_t n);
bool	line_realloc(t_line *line, size_t cap);
void	buffer_move(t_buffer *buffer, size_t index);
void	buffer_reset(t_buffer *buffer);

#endif
