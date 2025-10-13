#include "../test.h"

int	test_ft_strnstr(void)
{
	int		score;

	score = 0;
	score += test_str("ft_strnstr", "\"123456789\", \"\", 0", "123456789", ft_strnstr("123456789", "", 0));
	score += test_str("ft_strnstr", "\"123456789\", \"\", 9", "123456789", ft_strnstr("123456789", "", 9));
	score += test_str("ft_strnstr", "\"123456789\", \"\", 25", "123456789", ft_strnstr("123456789", "", 25));

	score += test_str("ft_strnstr", "\"123456789\", \"abc\", 0", "NULL", ft_strnstr("123456789", "abc", 0));
	score += test_str("ft_strnstr", "\"123456789\", \"abc\", 9", "NULL", ft_strnstr("123456789", "abc", 9));
	score += test_str("ft_strnstr", "\"123456789\", \"abc\", 25", "NULL", ft_strnstr("123456789", "abc", 25));

	score += test_str("ft_strnstr", "\"123456789\", \"456\", 0", "NULL", ft_strnstr("123456789", "456", 0));
	score += test_str("ft_strnstr", "\"123456789\", \"456\", 9", "456789", ft_strnstr("123456789", "456", 9));
	score += test_str("ft_strnstr", "\"123456789\", \"456\", 25", "456789", ft_strnstr("123456789", "456", 25));
	printf("\n");
	if (score == 9)
		return (1);
	return (0);
}
