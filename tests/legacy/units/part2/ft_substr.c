#include "../../test.h"

char	*get_args(const char *str, unsigned int start, size_t len);
int		unit_test_substr(const char *str, unsigned int start, size_t len, char *expected);

int	test_ft_substr(void)
{
	int		score;

	score = 0;
	score += unit_test_substr("123456789", 0, 0, "");
	score += unit_test_substr("123456789", 0, 9, "123456789");
	score += unit_test_substr("123456789", 4, 5, "56789");
	score += unit_test_substr("123456789", 4, 9, "56789");
	score += unit_test_substr(NULL, 0, 0, "NULL");
	printf("\n");
	if (score == 5)
		return (1);
	return (0);
}

int	unit_test_substr(const char *str, unsigned int start, size_t len, char *expected)
{
	char	*res;
	char	*args;

	args = get_args(str, start, len);
	if (!args)
	{
		printf("Error when creating args");
		return (0);
	}
	res = ft_substr(str, start, len);
	if (!res || strcmp(res, expected) != 0)
	{
		print_failure("ft_substr", args, res, expected);
		return (0);
	}
	print_success("ft_substr", args, res);
	free(args);
	free(res);
	return (1);
}

char	*format_str_arg(const char *str)
{
	char	*res;
	size_t	str_len;

	if (!str)
	{
		res = malloc(7);
		if (!res)
			return (NULL);
		res = "\"NULL\"";
	}
	else
	{
		str_len = ft_strlen(str);
		res = malloc(str_len + 3);
		if (!res)
			return (NULL);
		res[0] = '\"';
		strcat(res, str);
		res[str_len + 1] = '\"';
		res[str_len + 2] = '\0';
	}
	return (res);
}

char	*get_args(const char *str, unsigned int start, size_t len)
{
	char	*start_str;
	char	*len_str;
	char	*args[3];
	char	*res;

	start_str = ft_itoa(start);
	if (!start_str)
		return (NULL);
	len_str = ft_itoa(len);
	if (!len_str)
	{
		free(start_str);
		return (NULL);
	}
	args[0] = format_str_arg(str);
	if (!args[0])
	{
		free(start_str);
		free(len_str);
		return (NULL);
	}
	args[1] = start_str;
	args[2] = len_str;
	res = ft_strmultijoin(args, 3, ", ");
	printf("args[0] = %s\n", args[0]);
	free(args[0]);
	printf("args[0] freed\n");
	free(start_str);
	free(len_str);
	if (!res)
		return (NULL);
	return (res);
}
