#include <stddef.h>

size_t	modulo(long a, size_t b)
{
	long	res;

	res = a % (long)b;
	if (res < 0)
		res += (long)b;
	return ((size_t)res);
}
