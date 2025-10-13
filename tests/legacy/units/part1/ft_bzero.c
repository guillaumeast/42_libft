#include "../../test.h"

int	test_ft_bzero(void)
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
	ft_bzero(res, 0);
	score += test_str("ft_bzero", "\"0123456789\", 0", "123456789", res);
	ft_bzero(res, 1);
	score += test_str("ft_bzero", "\"0123456789\", 1", "", res);
	ft_bzero(res, 9);
	score += test_str("ft_bzero", "\"0123456789\", 9", "", res);
	printf("\n");
	if (score == 3)
		return (1);
	return (0);
}
