#include "test.h"

// TODO: Makefile (lib + test)
int	main(void)
{
	int	score;

	score = 0;

	// Part 1
	score += test_ft_isalpha();

	print_result(score, 1);
	return (0);
}
