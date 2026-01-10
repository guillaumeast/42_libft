/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 01:30:51 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:35:57 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Reallocates a buffer to a new capacity.
 *
 * @param buff Pointer to the buffer pointer.
 * @param cap Current capacity.
 * @param newcap New capacity (0 to free).
 * @return true on success, false on failure.
 */
bool	ft_realloc(char **buff, size_t cap, size_t newcap)
{
	char	*new_buff;
	size_t	i;

	if (newcap == 0)
	{
		free(*buff);
		*buff = NULL;
		return (true);
	}
	new_buff = malloc(newcap);
	if (!new_buff)
		return (false);
	i = 0;
	while (i < cap)
	{
		new_buff[i] = (*buff)[i];
		i++;
	}
	free(*buff);
	*buff = new_buff;
	return (true);
}
