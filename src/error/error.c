/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 23:30:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/02/01 23:30:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

/*
*	Prints "Error\n" to stderr followed by a custom formatted message
*	Optionaly prints errno value formatted with perror()
*	@warning: fallback and fmt must NOT be NULL, use print_err() otherwise
*	Note: fallback string is only used when fmt formatting fails
*	Note: '\n' is automatically added if print_errno = false
*/
void	fprint_err(bool print_errno, const char *fallback, const char *fmt, ...)
{
	va_list	ap;
	t_buff	buff;
	int		errno_backup;

	errno_backup = errno;
	va_start(ap, fmt);
	buff_init(&buff, 0);
	if (buff_append_vformat(&buff, fmt, ap) && buff_append(&buff, "\0", 1))
	{
		errno = errno_backup;
		print_err(print_errno, buff.data);
	}
	else
	{
		errno = errno_backup;
		print_err(print_errno, fallback);
	}
	buff_free(&buff);
	va_end(ap);
}

/*
*	Prints "Error\n" to stderr
*
*	Optionaly followed by a custom message and/or errno value formatted with perror()
*
*	Note: '\n' is automatically added if print_errno = false
*	Note: message can be NULL
*/
void	print_err(bool print_errno, const char *message)
{
	int		errno_backup;

	errno_backup = errno;
	write(STDERR_FILENO, "Error\n", 6);
	if (print_errno)
	{
		errno = errno_backup;
		perror(message);
	}
	else if (message)
	{
		write(STDERR_FILENO, message, str_len(message));
		write(STDERR_FILENO, "\n", 1);
	}
}
