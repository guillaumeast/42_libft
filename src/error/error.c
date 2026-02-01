/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:30:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/02 00:34:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void	_print(bool print_errno, int errno_val, const char *s, size_t len);

void	fprint_err(bool print_errno, const char *safe, const char *fmt, ...)
{
	va_list	ap;
	t_buff	buff;
	int		errno_backup;

	errno_backup = errno;
	va_start(ap, fmt);
	buff_init(&buff, 0);
	if (buff_append(&buff, safe, -1) && buff_append_vformat(&buff, fmt, ap))
		_print(print_errno, errno_backup, buff.data, buff.len);
	else
		_print(print_errno, errno_backup, safe, str_len(safe));
	buff_free(&buff);
	va_end(ap);
}

void	print_err(bool print_errno, const char *message)
{
	int		errno_backup;
	size_t	len;

	errno_backup = errno;
	if (message)
		len = str_len(message);
	else
		len = 0;
	_print(print_errno, errno_backup, message, len);
}

static void	_print(bool print_errno, int errno_val, const char *s, size_t len)
{
	const char	*err_string;

	write(STDERR_FILENO, "Error\n", 6);
	if (!print_errno && !s)
		return ;
	write(STDERR_FILENO, "⇢ ", str_len("⇢ "));
	if (s)
		write(STDERR_FILENO, s, len);
	if (s && print_errno)
		write(STDERR_FILENO, ": ", 2);
	if (print_errno)
	{
		err_string = strerror(errno_val);
		write(STDERR_FILENO, err_string, str_len(err_string));
	}
	write(STDERR_FILENO, "\n", 1);
}
