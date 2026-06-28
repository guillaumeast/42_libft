/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_cmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:27:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/28 14:07:49 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	string_cmp(const t_string *a, const t_string *b)
{
	size_t	i;

	if (a->len != b->len)
		return (false);
	i = 0;
	while (i < a->len)
	{
		if (a->data[i] != b->data[i])
			return (false);
		++i;
	}
	return (true);
}
