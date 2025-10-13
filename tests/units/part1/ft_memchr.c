#include "../../test.h"

int	test_ft_memchr(void)
{
	int		score;
	char	str[7];

	score = 0;
	str[0] = '1';
	str[1] = '2';
	str[2] = '3';
	str[3] = '1';
	str[4] = '2';
	str[5] = '3';
	str[6] = '\0';
	score += test_str("ft_memchr", "\"123123\", \'z\', 7", "NULL", ft_memchr(str, 'z', 7));
	score += test_str("ft_memchr", "\"123123\", \'1\', 7", "123123", ft_memchr(str, '1', 7));
	score += test_str("ft_memchr", "\"123123\", \'3\', 7", "3123", ft_memchr(str, '3', 7));
	score += test_str("ft_memchr", "\"123123\", \'\\0\', 7", "", ft_memchr(str, '\0', 7));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
