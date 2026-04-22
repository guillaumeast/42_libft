/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/04/23 00:27:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	buff_get_index(t_buff *buff, char c)
{
	size_t	i;

	i = 0;
	while (i < buff->len)
	{
		if (buff->data[i] == c)
			return ((int)i);
		i++;
	}
	return (-1);
}

char	*buff_get_string(t_buff *buff)
{
	char	*res;
	size_t	len;

	len = buff->len;
	if (buff->data[buff->len - 1] == '\0')
		len--;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res = ft_memcpy(res, buff->data, len);
	res[len] = '\0';
	return (res);
}
