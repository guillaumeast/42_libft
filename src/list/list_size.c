/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:37 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
