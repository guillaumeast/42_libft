#include <criterion/criterion.h>
#include <limits.h>
#include <stdlib.h>
#include "libft.h"

typedef struct {
	int			input;
	const char	*expected;
}	t_case;

Test(ft_itoa, full_tests)
{
	const t_case cases[] = {
		// basic numbers
		{0, "0"},
		{1, "1"},
		{-1, "-1"},
		{42, "42"},
		{-42, "-42"},
		{12345, "12345"},
		{-12345, "-12345"},

		// int limits
		{INT_MAX, "2147483647"},
		{INT_MIN, "-2147483648"},
	};

	// Basic correctness: non-NULL, exact string, fresh allocation
	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char *got = ft_itoa(cases[i].input);

		cr_expect_neq(got, NULL,
			"\033[31mft_itoa(%d)\033[0m = \033[33mNULL\033[0m (expected \033[33mallocated string\033[0m)",
			cases[i].input);

		if (got) {
			cr_expect_str_eq(got, cases[i].expected,
				"\033[31mft_itoa(%d)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].input, got, cases[i].expected);
			free(got);
		}
	}
}
