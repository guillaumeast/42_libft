/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 01:48:59 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*list_get_content(t_list list, bool (*select_function)(void*))
{
	t_node	*node;
	
	if (!list || !select_function)
		return (NULL);
	node = list;
	while (node)
	{
		if (select_function(node->content))
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

void	*list_get_content_n(t_list list, size_t index)
{
	t_node	*node;

	node = list_get_node_n(list, index);
	if (!node)
		return (NULL);
	return (node->content);
}

void	*list_get_content_last(t_list list)
{
	t_node	*last_node;
	
	last_node = list_get_node_last(list);
	if (!last_node)
		return (NULL);
	return (last_node->content);
}

t_node	*list_get_node_n(t_list list, size_t index)
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

t_node	*list_get_node_last(t_list list)
{
	t_node	*last_node;
	
	if (!list)
		return (NULL);
	last_node = list;
	while (last_node->next)
		last_node = last_node->next;
	return (last_node);
}
