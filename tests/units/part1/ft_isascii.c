#include "../../test.h"

int	test_ft_isascii(void)
{
	int	score;

	score = 0;
	score += test_int("ft_isascii", "-32", 0, ft_isascii(-32));
	score += test_int("ft_isascii", "32", 1, ft_isascii(32));
	score += test_int("ft_isascii", "9", 1, ft_isascii('9'));
	score += test_int("ft_isascii", "a", 1, ft_isascii('a'));
	score += test_int("ft_isascii", "128", 0, ft_isascii(128));
	printf("\n");
	if (score == 5)
		return (1);
	return (0);
}
