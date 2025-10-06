#include "libft.h"

// The memmove() function copies len bytes from string src to string dst.  The two strings may overlap; the copy is always done in a non-destructive manner.
void	*memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst || !src)
		return (dst);
	i = 0;
	// TODO: check if dst < src
	while (i < len)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}