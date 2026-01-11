/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_life_cycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 02:56:33 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:26:15 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
