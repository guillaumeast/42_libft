#include "../../test.h"

int	test_ft_strlcat(void)
{
	int		score;
	char	dst[10];

	score = 0;
	dst[0] = '1';
	dst[1] = '2';
	dst[2] = '3';
	dst[3] = '4';
	dst[4] = '\0';
	dst[5] = '\0';
	dst[6] = '\0';
	dst[7] = '\0';
	dst[8] = '\0';
	dst[9] = '\0';
	score += test_int("ft_strlcat", "\"1234\", \"12345\", 0", 5, ft_strlcat(dst, "12345", 0));
	score += test_str("ft_strlcat", "\"1234\", \"12345\", 0", "1234", dst);
	score += test_int("ft_strlcat", "\"1234\", \"12345\", 3", 8, ft_strlcat(dst, "12345", 3));
	score += test_str("ft_strlcat", "\"1234\", \"12345\", 3", "1234", dst);
	score += test_int("ft_strlcat", "\"1234\", \"12345\", 7", 9, ft_strlcat(dst, "12345", 7));
	score += test_str("ft_strlcat", "\"1234\", \"12345\", 7", "123412", dst);
	dst[4] = '\0';
	dst[5] = '\0';
	score += test_int("ft_strlcat", "\"1234\", \"12345\", 10", 9, ft_strlcat(dst, "12345", 10));
	score += test_str("ft_strlcat", "\"1234\", \"12345\", 10", "123412345", dst);
	printf("\n");
	if (score == 8)
		return (1);
	return (0);
}
