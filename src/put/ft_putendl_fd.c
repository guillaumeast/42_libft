/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:13 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:40:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/**
 * @brief Writes a string followed by newline to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		write(fd, "(null)", sizeof("(null)") - 1);
	else
		write(fd, s, ft_strlen(s));
	write(fd, "\n", 1);
}
