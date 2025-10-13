#include "../test.h"

int	test_ft_strdup(void)
{
	int		score;
	char	*res;

	score = 0;
	res = ft_strdup("123456");
	if (!res)
	{
		print_failure("ft_strdup", "\"123456\"", "NULL", "123456");
		return (0);
	}
	score += test_str("ft_strdup", "\"123456\"", "123456", res);
	free(res);
	printf("\n");
	if (score == 1)
		return (1);
	return (0);
}
