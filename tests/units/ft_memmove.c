#include "../test.h"

int	test_ft_memmove(void)
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
	score += test_str("ft_memmove", "\"123456789\", \"abcdefghi\", 0", "123456789", ft_memmove(dst, "abcdefghi", 0));
	score += test_str("ft_memmove", "\"123456789\", \"abcdefghi\", 1", "a23456789", ft_memmove(dst, "abcdefghi", 1));
	score += test_str("ft_memmove", "\"a23456789\", \"abcdefghi\", 5", "abcde6789", ft_memmove(dst, "abcdefghi", 5));
	score += test_str("ft_memmove", "\"abcde6789\", \"abcdefghi\", 9", "abcdefghi", ft_memmove(dst, "abcdefghi", 9));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
