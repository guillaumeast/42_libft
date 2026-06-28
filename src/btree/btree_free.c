/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:41:00 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:41:01 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
