#include "../../test.h"

int	test_ft_isalnum(void)
{
	int	score;

	score = 0;
	score += test_int("ft_isalnum", "-32", 0, ft_isalnum(-32));
	score += test_int("ft_isalnum", "32", 0, ft_isalnum(32));
	score += test_int("ft_isalnum", "9", 1, ft_isalnum('9'));
	score += test_int("ft_isalnum", "a", 1, ft_isalnum('a'));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
