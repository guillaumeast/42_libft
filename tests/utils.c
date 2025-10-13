#include "test.h"

// Test a function which returns an int
int	test_int(char *f_name, char *input, int expected_output, int output)
{
	if (expected_output == output)
	{
		print_success(f_name, input, ft_itoa(output));
		return (1);
	}
	print_failure(f_name, input, ft_itoa(output), ft_itoa(expected_output));
	return (0);
}

// Test a function which returns a string
int	test_str(char *f_name, char *input, char *expected_output, char *output)
{
	if (strcmp(output, expected_output) == 0)
	{
		print_success(f_name, input, output);
		return (1);
	}
	print_failure(f_name, input, output, expected_output);
	return (0);
}

// Print success in green
void	print_success(char *f_name, char *input, char *output)
{
	printf("\x1b[32m✓\x1b[0m ");
	printf("%s(%s) => \x1b[32m\"%s\"\x1b[0m\n", f_name, input, output);
}

// Print failure in bold red
void	print_failure(char *f_name, char *input, char *output, char *expected)
{
	printf("\x1b[31m⨯\x1b[0m ");
	printf("%s(%s) => ", f_name, input);
	printf("\x1b[1;31m\"%s\"\x1b[0m (expected \"%s\")\n", output, expected);
}

// Print part score
void	print_result(int score, int max_score)
{
	char	*color;

	if(score == max_score)
		color = "\x1b[32m";
	else
		color = "\x1b[1;31m";
	printf("%s---> RESULT = %d / %d\x1b[0m\n", color, score, max_score);
}
