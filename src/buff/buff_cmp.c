/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buff_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 18:27:52 by adouieb           #+#    #+#             */
/*   Updated: 2026/05/28 18:29:55 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	buff_cmp(const t_buff *a, const t_buff *b)
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
