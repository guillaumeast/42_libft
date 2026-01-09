#include "libft.h"
#include <stdlib.h>

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
