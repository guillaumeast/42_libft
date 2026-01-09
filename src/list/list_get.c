/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 00:51:00 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

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

t_node	*list_get_n(t_list list, size_t index)
{
	t_node	*node;

	if (!list)
		return (NULL);
	node = list;
	while (node && index)
	{
		node = node->next;
		index--;	
	}
	if (index > 0)
		return (NULL);
	return (node);
}

t_node	*list_get_last(t_list list)
{
	t_node	*last_node;
	
	if (!list)
		return (NULL);
	last_node = list;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}
