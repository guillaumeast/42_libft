/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 00:34:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/**
 * @brief Applies a function to each element of the list.
 *
 * @param lst List to iterate over.
 * @param f Function to apply to each element's content.
 */
void	list_iter(t_list lst, void (*f)(void *))
{
	t_node	*node;

	if (!lst || !f)
		return ;
	node = lst;
	while (node)
	{
		f(node->content);
		node = node->next;
	}
}

/**
 * @brief Creates a new list by applying a function to each element.
 *
 * @param list Source list.
 * @param f Function to apply to each element.
 * @param del Function to delete elements on failure (can be NULL).
 * @return New list, or NULL on failure.
 */
t_list	list_map(t_list list, void *(*f)(void *), void (*del)(void *))
{
	t_node	*node;
	t_list	new_list;
	void	*new_content;

	if (!list || !f || !del)
		return (NULL);
	node = list;
	new_list = NULL;
	while (node)
	{
		new_content = f(node->content);
		if (!list_add_end(&new_list, new_content))
		{
			del(new_content);
			list_rm_all(&new_list, del);
			return (NULL);
		}
		node = node->next;
	}
	return (new_list);
}
