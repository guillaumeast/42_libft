/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:44:48 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 16:26:20 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "key_value.h"

bool	bucket_contains(t_list bucket, char *key)
{
	t_key_value	*pair;
	t_node		*entry;

	entry = bucket;
	while (entry != NULL)
	{
		pair = entry->content;
		if (is_matching_key(pair, key))
			return (true);
		entry = entry->next;
	}
	return (false);
}
