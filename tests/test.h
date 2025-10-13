#ifndef TEST_H
# define TEST_H

// TODO: replace by libft.a
# include "libft.h"
# include <string.h>	// strcmp

// Utils
int		test_int(char *f_name, char *input, int expected_output, int output);
int		test_str(char *f_name, char *input, char *expected_output, char *output);
void	print_success(char *f_name, char *input, char *output);
void	print_failure(char *f_name, char *input, char *output, char *expected);
void	print_result(int score, int max_score);

// Tests
int		test_ft_isalpha(void);

#endif