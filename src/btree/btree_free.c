#include "libft.h"
#include <stdlib.h>

void	btree_free(t_btree_node **node, void (*data_free)(void *data))
{
	if (!node || !*node)
		return ;
	btree_free(&(*node)->left, data_free);
	btree_free(&(*node)->right, data_free);
	if ((*node)->data && data_free)
		data_free((*node)->data);
	free(*node);
	*node = NULL;
}
