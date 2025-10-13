#include "../test.h"

int	test_ft_toupper(void)
{
	int		score;

	score = 0;
	score += test_int("ft_toupper", "\'a\'", 'A', ft_toupper('a'));
	score += test_int("ft_toupper", "\'A\'", 'A', ft_toupper('A'));
	score += test_int("ft_toupper", "\'1\'", '1', ft_toupper('1'));
	printf("\n");
	if (score == 3)
		return (1);
	return (0);
}
