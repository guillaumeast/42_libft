#include "../test.h"

int	test_ft_isprint(void)
{
	int	score;

	score = 0;
	score += test_int("ft_isprint", "-32", 0, ft_isprint(-32));
	score += test_int("ft_isprint", "32", 1, ft_isprint(32));
	score += test_int("ft_isprint", "9", 1, ft_isprint('9'));
	score += test_int("ft_isprint", "a", 1, ft_isprint('a'));
	score += test_int("ft_isprint", "127", 0, ft_isprint(127));
	printf("\n");
	if (score == 5)
		return (1);
	return (0);
}
