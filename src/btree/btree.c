/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 14:40:56 by gastesan          #+#    #+#             */
/*   Updated: 2026/06/28 14:40:57 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_btree_node	*btree_new(void *data)
{
	t_btree_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (NULL);
	node->data = data;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	btree_set_left(t_btree_node *parent, t_btree_node *child)
{
	parent->left = child;
	child->parent = parent;
}

void	btree_set_right(t_btree_node *parent, t_btree_node *child)
{
	parent->right = child;
	child->parent = parent;
}

t_btree_node	*btree_detach_left(t_btree_node *parent)
{
	t_btree_node	*left;

	left = parent->left;
	parent->left = NULL;
	left->parent = NULL;
	return (left);
}

t_btree_node	*btree_detach_right(t_btree_node *parent)
{
	t_btree_node	*right;

	right = parent->right;
	parent->right = NULL;
	right->parent = NULL;
	return (right);
}
