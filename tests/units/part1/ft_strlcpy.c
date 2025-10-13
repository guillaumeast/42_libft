#include "../../test.h"

int	test_ft_strlcpy(void)
{
	int		score;
	char	dst[10];

	score = 0;
	dst[0] = '1';
	dst[1] = '2';
	dst[2] = '3';
	dst[3] = '4';
	dst[4] = '5';
	dst[5] = '6';
	dst[6] = '7';
	dst[7] = '8';
	dst[8] = '9';
	dst[9] = '\0';
	score += test_int("ft_strlcpy", "\"123456789\", \"abcdefghi\", 0", 9, ft_strlcpy(dst, "abcdefghi", 0));
	score += test_str("ft_strlcpy", "\"123456789\", \"abcdefghi\", 0", "123456789", dst);
	score += test_int("ft_strlcpy", "\"123456789\", \"abcdefghi\", 10", 9, ft_strlcpy(dst, "abcdefghi", 10));
	score += test_str("ft_strlcpy", "\"123456789\", \"abcdefghi\", 10", "abcdefghi", dst);
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
