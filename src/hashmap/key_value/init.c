/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:34:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:43:53 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_key_value	*key_value_new(const char *key, void *value)
{
	t_key_value	*pair;

	pair = malloc(sizeof(t_key_value));
	if (pair == NULL)
		return (NULL);
	pair->key = str_dup(key);
	if (pair->key == NULL)
		return (free(pair), NULL);
	return (pair->value = value, pair);
}

void	key_value_free(t_key_value **pair, void (*del)(void *))
{
	if (pair == NULL || *pair == NULL)
		return ;	
	if (del)
		del((*pair)->value);
	free((*pair)->key);
	**pair = (t_key_value){0};
	free(*pair);
	*pair = NULL;
}
