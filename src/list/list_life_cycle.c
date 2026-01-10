/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:34:48 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/**
 * @brief Adds a new element at the start of the list.
 *
 * @param list Pointer to the list.
 * @param new_content Content for the new node.
 * @return true on success, false on failure.
 */
bool	list_add_start(t_list *list, void *new_content)
{
	t_node	*new_node;

	if (!list)
		return (false);
	new_node = node_new(new_content, NULL, *list);
	if (!new_node)
		return (false);
	if (*list)
		(*list)->prev = new_node;
	*list = new_node;
	return (true);
}

/**
 * @brief Adds a new element at the end of the list.
 *
 * @param list Pointer to the list.
 * @param new_content Content for the new node.
 * @return true on success, false on failure.
 */
bool	list_add_end(t_list *list, void *new_content)
{
	t_node	*new_node;
	t_node	*last_node;

	if (!list)
		return (false);
	new_node = node_new(new_content, NULL, NULL);
	if (!new_node)
		return (false);
	if (!*list)
	{
		*list = new_node;
		return (true);
	}
	last_node = *list;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = new_node;
	new_node->prev = last_node;
	return (true);
}

/**
 * @brief Removes a specific node from the list.
 *
 * @param list Pointer to the list.
 * @param node Node to remove.
 * @param del_content Function to delete the node's content (can be NULL).
 */
void	list_rm(t_list *list, t_node *node, void (*del_content)(void*))
{
	t_node	*prev;
	t_node	*next;

	if (!list || !node)
		return ;
	prev = node->prev;
	next = node->next;
	if (prev)
		prev->next = node->next;
	else
		*list = next;
	if (next)
		next->prev = node->prev;
	if (del_content)
		del_content(node->content);
	free(node);
}

/**
 * @brief Removes all nodes from the list.
 *
 * @param list Pointer to the list.
 * @param del_content Function to delete each node's content (can be NULL).
 */
void	list_rm_all(t_list *list, void (*del_content)(void*))
{
	t_node	*node;
	t_node	*next;

	if (!list)
		return ;
	node = *list;
	while (node)
	{
		next = node->next;
		if (del_content)
			del_content(node->content);
		free(node);
		node = next;
	}
	*list = NULL;
	return ;
}
