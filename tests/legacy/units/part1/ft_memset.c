#include "../../test.h"

int	test_ft_memset(void)
{
	int		score;
	char	res[10];

	score = 0;
	res[0] = '1';
	res[1] = '2';
	res[2] = '3';
	res[3] = '4';
	res[4] = '5';
	res[5] = '6';
	res[6] = '7';
	res[7] = '8';
	res[8] = '9';
	res[9] = '\0';
	score += test_str("ft_memset", "\"0123456789\", \'a\', 0", "123456789", ft_memset(res, 'a', 0));
	score += test_str("ft_memset", "\"0123456789\", \'a\', 1", "a23456789", ft_memset(res, 'a', 1));
	score += test_str("ft_memset", "\"0123456789\", \'a\', 5", "aaaaa6789", ft_memset(res, 'a', 5));
	score += test_str("ft_memset", "\"0123456789\", \'a\', 9", "aaaaaaaaa", ft_memset(res, 'a', 9));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
