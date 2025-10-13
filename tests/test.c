#include "test.h"

// TODO: Makefile (lib + test)
int	main(void)
{
	int	score;

	score = 0;

	// Part 1
	score += test_ft_isalpha();
	score += test_ft_isdigit();
	score += test_ft_isalnum();
	score += test_ft_isascii();
	score += test_ft_isprint();

	print_result(score, 5);
	return (0);
}
