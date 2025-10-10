#include "libft.h"

/*
strlcpy() take the full size of the destination buffer and guarantee NUL-termination if there is room.
Room for the NUL should be included in dstsize.
strlcpy() only operate on true ''C'' strings: src must be NUL-terminated.
strlcpy() function returns the length of src.
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	if (!dst || dstsize == 0)
		return (src_len);
	i = 0;
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
