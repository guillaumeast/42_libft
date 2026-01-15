#include <stdbool.h>
#include <limits.h>

bool	parse_int(char *s, int *out)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (*s == '\0')
		return (false);
	while (*s)
	{
		if (*s < '0' || *s > '9' || result > (LONG_MAX - (*s - '0')) / 10)
			return (false);
		result = result * 10 + (*s - '0');
		s++;
	}
	result *= sign;
	if (result < INT_MIN || result > INT_MAX)
		return (false);
	*out = (int)result;
	return (true);
}
