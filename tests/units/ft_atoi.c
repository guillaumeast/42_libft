#include "../test.h"

int	test_ft_atoi(void)
{
	int	score;

	score = 0;
	score += test_int("ft_atoi", "\"abc\"", 0, ft_atoi("abc"));
	score += test_int("ft_atoi", "\"abc123\"", 0, ft_atoi("abc123"));
	score += test_int("ft_atoi", "\"--123\"", 0, ft_atoi("--123"));
	score += test_int("ft_atoi", "\"  \\t\\n\\v\\f\\r 0abc\"", 0, ft_atoi("  \t\n\v\f\r 0abc"));
	score += test_int("ft_atoi", "\"  \\t\\n\\v\\f\\r +2147483647abc\"", 2147483647, ft_atoi("  \t\n\v\f\r +2147483647abc"));
	score += test_int("ft_atoi", "\"  \\t\\n\\v\\f\\r -2147483648abc\"", -2147483648, ft_atoi("  \t\n\v\f\r -2147483648abc"));
	printf("\n");
	if (score == 6)
		return (1);
	return (0);
}
