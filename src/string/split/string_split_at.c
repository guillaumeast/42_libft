/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_split_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 19:39:29 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/07 12:47:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	string_split_at(
			const t_string *src,
			size_t index,
			t_string *out_before,
			t_string *out_after)
{
	if (index >= src->len)
	{
		if (!string_dup(out_before, src))
			return (false);
		if (!string_init(out_after, 1, "", 0))
			return (string_free(out_before), false);
		return (true);
	}
	if (!string_init(out_before, 0, src->data, (long)index))
		return (false);
	if (!string_init(out_after, 0, src->data + index, (long)(src->len - index)))
		return (string_free(out_before), false);
	return (true);
}
