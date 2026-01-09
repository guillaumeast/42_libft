#include "libft.h"
#include <stdlib.h>

t_node	*node_new(void *content, t_node *prev, t_node *next)
{
	t_node	*new_node;

	new_node = malloc(sizeof *new_node);
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->prev = prev;
	new_node->next = next;
	return (new_node);
}

void	node_free(t_node **node, void (*del_content)(void*))
{
	if (!node || !*node)
		return ;
	if (del_content)
		del_content((*node)->content);
	free(*node);
	*node = NULL;
}
