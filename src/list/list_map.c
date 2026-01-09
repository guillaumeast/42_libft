/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:19:48 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/10 00:39:13 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

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
