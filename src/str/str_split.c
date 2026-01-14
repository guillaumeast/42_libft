/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:20:20 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/14 03:46:41 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static char		*get_word(char const *s, char sep);

char	**str_split(char const *s, char c)
{
	size_t	i;
	char	**res;

	if (!s)
		return (NULL);
	res = malloc((str_count_words(s, c) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			res[i] = NULL;
			res[i] = get_word(s, c);
			if (!res[i++])
				return (str_array_free(&res), NULL);
			while (*s && *s != c)
				s++;
			continue ;
		}
		s++;
	}
	res[i] = NULL;
	return (res);
}

size_t	str_count_words(char const *s, char sep)
{
	size_t	count;
	char	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && *s != sep)
		{
			in_word = 1;
			count++;
		}
		else if (in_word && *s == sep)
			in_word = 0;
		s++;
	}
	return (count);
}

/**
 * @brief Extracts a word from a string until the separator.
 *
 * @param s String to extract from.
 * @param sep Delimiter character.
 * @return Newly allocated word, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
static char	*get_word(char const *s, char sep)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != sep)
		len++;
	return (str_sub(s, 0, len));
}

void	str_array_free(char ***tab_ptr)
{
	size_t	i;

	i = 0;
	while ((*tab_ptr)[i])
		free((*tab_ptr)[i++]);
	free(*tab_ptr);
	*tab_ptr = NULL;
}
