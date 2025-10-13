#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	int			tested_char;
	int			expected_output;
	const char	*label;
}	t_case;

Test(ft_isascii, full_tests)
{
	const t_case cases[] = {
		// In-range ASCII (should return non-zero)
		{'\0', 1, "\'\\0\'"},
		{'\n', 1, "\'\\n\'"},
		{'A', 1, "\'A\'"},
		{'z', 1, "\'z\'"},
		{31, 1, "31"},
		{' ', 1, "\' \'"},
		{126, 1, "126"},
		{127, 1, "127"},

		// Out-of-range (should return 0)
		{-1, 0, "-1"},
		{-42, 0, "-42"},
		{128, 0, "128"},
		{200, 0, "200"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got = ft_isascii(cases[i].tested_char);
		if (cases[i].expected_output)
			cr_expect_neq(got, 0, "\033[31mft_isascii(%s)\033[0m = \033[33m%d\033[0m (expected \033[33mnon-zero\033[0m)", cases[i].label, got);
		else
			cr_expect_eq(got, 0, "\033[31mft_isascii(%s)\033[0m = \033[33m%d\033[0m (expected \033[33m0\033[0m)", cases[i].label, got);
	}
}
