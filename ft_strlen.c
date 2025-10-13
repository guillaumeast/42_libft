/*
Computes the length of the string s.
---
Returns the number of characters that precede the terminating NUL character.
*/

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
