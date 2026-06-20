/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:37:44 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/20 13:50:11 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	is_matching_key(t_key_value *pair, const char *key)
{
	return (str_ncmp(pair->key, key, str_len(key) + 1) == 0);
}
