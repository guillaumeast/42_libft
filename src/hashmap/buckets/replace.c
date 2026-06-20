/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:43:08 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 15:15:34 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "key_value.h"

void	bucket_replace(t_list bucket, t_key_value *new, void (*del)(void *))
{
	t_key_value	*pair;
	t_node		*entry;
	
	entry = bucket;
	while (entry != NULL)
	{
		pair = entry->content;
		if (is_matching_key(pair, new->key))
		{
			key_value_free(&pair, del);
			entry->content = new;
			return;
		}
		entry = entry->next;
	}
}
