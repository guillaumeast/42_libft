/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pidtoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 15:40:17 by gastesan          #+#    #+#             */
/*   Updated: 2026/05/19 15:40:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>

static size_t	get_len(pid_t n);
static void		populate(pid_t n, char *str, size_t i);

char	*ft_pidtoa(pid_t n)
{
	size_t	len;
	char	*res;

	len = get_len(n);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res[len] = '\0';
	if (n < 0)
		res[0] = '-';
	populate(n, res, len - 1);
	return (res);
}

static size_t	get_len(pid_t n)
{
	size_t	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10 != 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	populate(pid_t n, char *str, size_t i)
{
	int	mod;

	if (n >= 10 || n <= -10)
		populate(n / 10, str, i - 1);
	mod = n % 10;
	if (mod < 0)
		mod *= -1;
	str[i] = (char)mod + '0';
}
