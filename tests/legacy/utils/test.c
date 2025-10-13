#include "../test.h"

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
	if (!output && strcmp(expected_output, "NULL") == 0)
	{
		print_success(f_name, input, "NULL");
		return (1);
	}
	if (!output)
	{
		print_failure(f_name, input, "NULL", expected_output);
		return (0);
	}
	if (strcmp(output, expected_output) == 0)
	{
		print_success(f_name, input, output);
		return (1);
	}
	print_failure(f_name, input, output, expected_output);
	return (0);
}
