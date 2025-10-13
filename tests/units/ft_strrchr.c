#include "../test.h"

int	test_ft_strrchr(void)
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
	score += test_str("ft_strrchr", "\"123123\", \'z\'", "NULL", ft_strrchr(str, 'z'));
	score += test_str("ft_strrchr", "\"123123\", \'1\'", "123", ft_strrchr(str, '1'));
	score += test_str("ft_strrchr", "\"123123\", \'3\'", "3", ft_strrchr(str, '3'));
	score += test_str("ft_strrchr", "\"123123\", \'\\0\'", "", ft_strrchr(str, '\0'));
	printf("\n");
	if (score == 4)
		return (1);
	return (0);
}
