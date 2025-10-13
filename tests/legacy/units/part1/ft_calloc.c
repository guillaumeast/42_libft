#include "../../test.h"

int	test_ft_calloc(void)
{
	int		score;
	char	*res;
	char	tmp[7];
	int		i;

	score = 0;
	res = ft_calloc(4, sizeof(char));
	if (!res)
	{
		print_failure("ft_calloc", "4, sizeof(char)", "NULL", "");
		return (0);
	}
	score += test_str("ft_calloc", "4, sizeof(char)", "", res);
	i = 0;
	tmp[0] = 'r';
	tmp[1] = 'e';
	tmp[2] = 's';
	tmp[3] = '[';
	tmp[5] = ']';
	tmp[6] = '\0';
	while (i < 4)
	{
		tmp[4] = i + '0';
		score += test_int(tmp, "", 0, res[i]);
		i++;
	}
	free(res);
	printf("\n");
	if (score == 5)
		return (1);
	return (0);
}
