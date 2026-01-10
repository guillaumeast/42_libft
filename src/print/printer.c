/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 22:44:22 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 22:44:23 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

int	ft_vdprintf(int fd, const char *fstring, va_list args)
{
	t_buff	buff;
	bool	success;
	int		written;

	if (fd == -1)
		return (-1);
	if (!buff_init(&buff, 0))
		return (-1);
	success = buff_append_vformat(&buff, fstring, args);
	written = (int)write(fd, buff.data, buff.len);
	buff_free(&buff);
	if (!success)
		return (-1);
	return (written);
}

int	ft_dprintf(int fd, const char *fstring, ...)
{
	va_list	args;
	int		written;

	if (fd == -1)
		return (-1);
	va_start(args, fstring);
	written = ft_vdprintf(fd, fstring, args);
	va_end(args);
	return (written);
}

int	ft_vprintf(const char *fstring, va_list args)
{
	return (ft_vdprintf(STDOUT_FILENO, fstring, args));
}

int	ft_printf(const char *fstring, ...)
{
	va_list	args;
	int		written;

	va_start(args, fstring);
	written = ft_vprintf(fstring, args);
	va_end(args);
	return (written);
}
