/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/27 17:40:08 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

bool	buff_adjust(t_buff *const buff)
{
	char	*new_data;

	if (buff->cap == buff->len)
		return (true);
	else if (buff->len == 0)
	{
		if (buff->data)
			free(buff->data);
		buff->data = NULL;
		buff->cap = 0;
		return (true);
	}
	new_data = malloc(buff->len);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, buff->data, buff->len);
	free(buff->data);
	buff->data = new_data;
	buff->cap = buff->len;
	return (true);
}

ssize_t	buff_get_index_c(const t_buff *const buff, char c)
{
	size_t	i;

	i = 0;
	while (i < buff->len)
	{
		if (buff->data[i] == c)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}

ssize_t	buff_get_index_s(
	const t_buff *const buff,
	const char *const s,
	ssize_t slen)
{
	size_t	i;
	size_t	j;

	if (buff->len == 0 || slen == 0)
		return (-1);
	if (slen < 0)
		slen = (ssize_t)str_len(s);
	if ((size_t)slen > buff->len)
		return (-1);
	i = 0;
	while (i < buff->len)
	{
		j = 0;
		while (j < (size_t)slen
			&& i + j < buff->len
			&& buff->data[i + j] == s[j])
			j++;
		if (j == (size_t)slen)
			return ((ssize_t)i);
		i++;
	}
	return (-1);
}

char	*buff_get_string(const t_buff *const buff)
{
	char		*res;
	size_t		len;

	len = buff->len;
	while (len > 0 && buff->data[len - 1] == '\0')
		len--;
	if (len == 0)
		return (str_dup(""));
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	res = ft_memcpy(res, buff->data, len);
	res[len] = '\0';
	return (res);
}
