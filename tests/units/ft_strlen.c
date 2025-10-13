#include "../test.h"

int	test_ft_strlen(void)
{
	int	score;

	score = 0;
	score += test_int("ft_strlen", "", 0, ft_strlen(""));
	score += test_int("ft_strlen", "1", 1, ft_strlen("1"));
	score += test_int("ft_strlen", "0123456789", 10, ft_strlen("0123456789"));
	score += test_int("ft_strlen", "1 3", 3, ft_strlen("1 3"));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
