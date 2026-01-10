/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:34:58 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the number of nodes in the list.
 *
 * @param list List to count.
 * @return Number of nodes in the list.
 */
size_t	list_get_size(t_list list)
{
	size_t	size;
	t_node	*node;

	node = list;
	size = 0;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}
