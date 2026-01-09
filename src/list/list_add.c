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
