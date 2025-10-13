#include "../../test.h"

int	test_ft_isalpha(void)
{
	int	score;

	score = 0;
	score += test_int("ft_isalpha", "-32", 0, ft_isalpha(-32));
	score += test_int("ft_isalpha", "32", 0, ft_isalpha(32));
	score += test_int("ft_isalpha", "9", 0, ft_isalpha('9'));
	score += test_int("ft_isalpha", "a", 1, ft_isalpha('a'));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
