#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	int			tested_char;
	int			expected_output;
	const char	*label;
}	t_case;

Test(ft_isprint, full_tests)
{
	const t_case cases[] = {
		// Printable ASCII characters (should return non-zero)
		{' ', 1, "\' \'"},
		{'!', 1, "\'!\'"},
		{'A', 1, "\'A\'"},
		{'z', 1, "\'z\'"},
		{'0', 1, "\'0\'"},
		{'~', 1, "\'~\'"},

		// Non-printable control characters (should return 0)
		{'\0', 0, "\'\\0\'"},
		{'\n', 0, "\'\\n\'"},
		{'\t', 0, "\'\\t\'"},
		{31, 0, "31"},
		{127, 0, "127"},

		// Out-of-range values (should return 0)
		{-42, 0, "-42"},
		{128, 0, "128"},
		{255, 0, "255"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got = ft_isprint(cases[i].tested_char);
		if (cases[i].expected_output)
			cr_expect_neq(got, 0, "\033[31mft_isprint(%s)\033[0m = \033[33m%d\033[0m (expected \033[33mnon-zero\033[0m)", cases[i].label, got);
		else
			cr_expect_eq(got, 0, "\033[31mft_isprint(%s)\033[0m = \033[33m%d\033[0m (expected \033[33m0)\033[0m", cases[i].label, got);
	}
}
