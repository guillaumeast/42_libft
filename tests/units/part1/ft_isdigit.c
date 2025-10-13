#include "../../test.h"

int	test_ft_isdigit(void)
{
	int	score;

	score = 0;
	score += test_int("ft_isdigit", "-32", 0, ft_isdigit(-32));
	score += test_int("ft_isdigit", "32", 0, ft_isdigit(32));
	score += test_int("ft_isdigit", "9", 1, ft_isdigit('9'));
	score += test_int("ft_isdigit", "a", 0, ft_isdigit('a'));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
