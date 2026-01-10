/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 19:29:25 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:19:51 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Finds the index of a character in the buffer.
 *
 * @param buff Pointer to the buffer.
 * @param c Character to find.
 * @return Index of the character, or -1 if not found.
 */
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
