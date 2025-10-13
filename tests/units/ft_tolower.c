#include "../test.h"

int	test_ft_tolower(void)
{
	int		score;

	score = 0;
	score += test_int("ft_tolower", "\'a\'", 'a', ft_tolower('a'));
	score += test_int("ft_tolower", "\'A\'", 'a', ft_tolower('A'));
	score += test_int("ft_tolower", "\'1\'", '1', ft_tolower('1'));
	printf("\n");
	if (score == 3)
		return (1);
	return (0);
}
