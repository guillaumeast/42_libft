/*
Writes len bytes of value c (converted to an unsigned char) to the string b.
---
Returns its first argument.
*/

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
}
