/*
Locates the first occurrence of c (converted to a char) in the string pointed to by s.
The terminating null character is considered part of the string.
Therefore if c is ‘\0’, the functions locate the terminating ‘\0’.
---
Returns a pointer to the located character, or NULL if the character does not appear in the string.
*/

#include "libft.h"

char	*strchr(const char *s, int c)
{
	char	*p;
	char	target;

	p = (char *) s;
	target = (char) c;
	while (*p)
	{
		if (*p == target)
			return (p);
		p++;
	}
	if (*p == '\0' && target == '\0')
		return (p);
	return (NULL);
}