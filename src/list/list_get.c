/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:45 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:33:33 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/**
 * @brief Finds content in list matching a selection function.
 *
 * @param list List to search.
 * @param select_function Function returning true for desired content.
 * @return Matching content, or NULL if not found.
 */
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

/**
 * @brief Gets content at a specific index in the list.
 *
 * @param list List to search.
 * @param index Zero-based index.
 * @return Content at index, or NULL if index out of bounds.
 */
void	*list_get_content_n(t_list list, size_t index)
{
	t_node	*node;

	node = list_get_node_n(list, index);
	if (!node)
		return (NULL);
	return (node->content);
}

/**
 * @brief Gets the content of the last node in the list.
 *
 * @param list List to search.
 * @return Content of last node, or NULL if list is empty.
 */
void	*list_get_content_last(t_list list)
{
	t_node	*last_node;

	last_node = list_get_node_last(list);
	if (!last_node)
		return (NULL);
	return (last_node->content);
}

/**
 * @brief Gets the node at a specific index in the list.
 *
 * @param list List to search.
 * @param index Zero-based index.
 * @return Node at index, or NULL if index out of bounds.
 */
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

/**
 * @brief Gets the last node in the list.
 *
 * @param list List to search.
 * @return Last node, or NULL if list is empty.
 */
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
