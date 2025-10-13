#include "test.h"

static void	test_part1(int *score);
static void	test_part2(int *score);
static void	test_bonus(int *score);

// TODO: Makefile (lib + test)
int	main(void)
{
	int	score;

	score = 0;
	test_part1(&score);
	test_part2(&score);
	test_bonus(&score);
	print_result(score, 23);
	return (0);
}

static void	test_part1(int *score)
{
	*score += test_ft_isalpha();
	*score += test_ft_isdigit();
	*score += test_ft_isalnum();
	*score += test_ft_isascii();
	*score += test_ft_isprint();
	*score += test_ft_strlen();
	*score += test_ft_memset();
	*score += test_ft_bzero();
	*score += test_ft_memcpy();
	*score += test_ft_memmove();
	*score += test_ft_strlcpy();
	*score += test_ft_strlcat();
	*score += test_ft_toupper();
	*score += test_ft_tolower();
	*score += test_ft_strchr();
	*score += test_ft_strrchr();
	*score += test_ft_strncmp();
	*score += test_ft_memchr();
	*score += test_ft_memcmp();
	*score += test_ft_strnstr();
	*score += test_ft_atoi();
	*score += test_ft_calloc();
	*score += test_ft_strdup();
}

static void	test_part2(int *score)
{
	*score = *score;
}

static void	test_bonus(int *score)
{
	*score = *score;
}
