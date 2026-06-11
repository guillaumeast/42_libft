/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adouieb <adouieb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 15:52:29 by adouieb           #+#    #+#             */
/*   Updated: 2026/06/11 18:44:23 by adouieb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	hash_string(const char *key)
{
	size_t	i;
	size_t	hash;

	i = 0;
	hash = 5381;
	while (key[i] != '\0')
		hash = ((hash << 5) + hash) + (unsigned char)key[i++];
	return (hash);
}
