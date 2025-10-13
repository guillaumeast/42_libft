#include "../test.h"

int	test_ft_memcmp(void)
{
	int		score;

	score = 0;
	score += test_int("ft_memcmp", "\"123456789\", \"123\", 0", 0, ft_memcmp("123456789", "123", 0));
	score += test_int("ft_memcmp", "\"123456789\", \"123\", 3", 0, ft_memcmp("123456789", "123", 3));
	score += test_int("ft_memcmp", "\"123456789\", \"123\", 6", 52, ft_memcmp("123456789", "123", 6));
	score += test_int("ft_memcmp", "\"123456789\", \"123\", 25", 52, ft_memcmp("123456789", "123", 25));
	score += test_int("ft_memcmp", "\"123456789\", \"123456789\", 25", 0, ft_memcmp("123456789", "123456789", 25));
	printf("\n");
	if (score == 5)
		return (1);
	return (0);
}
