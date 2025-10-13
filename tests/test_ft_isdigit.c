#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	int			tested_char;
	int			expected_output;
	const char	*label;
}	t_case;

Test(ft_isdigit, full_tests)
{
	const t_case cases[] = {
		// Digits (should return non-zero)
		{'0', 1, "\'0\'"},
		{'1', 1, "\'1\'"},
		{'5', 1, "\'5\'"},
		{'9', 1, "\'9\'"},

		// Letters (should return 0)
		{'a', 0, "\'a\'"},
		{'Z', 0, "\'Z\'"},

		// Symbols adjacent to digits in ASCII table (should return 0)
		{'/', 0, "\'/\'"},
		{':', 0, "\':\'"},

		// Whitespace and control characters (should return 0)
		{' ', 0, "\' \'"},
		{'\n', 0, "\'\\n\'"},
		{'\0', 0, "\'\\0\'"},

		// Out-of-range and extended ASCII values (should return 0)
		{-42, 0, "-42"},
		{127, 0, "127"},
		{200, 0, "200"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got = ft_isdigit(cases[i].tested_char);
		if (cases[i].expected_output)
			cr_expect_neq(got, 0, "\033[31mft_isdigit(%s)\033[0m = \033[33m%d\033[0m (expected \033[33mnon-zero\033[0m)", cases[i].label, got);
		else
			cr_expect_eq(got, 0, "\033[31mft_isdigit(%s)\033[0m = \033[33m%d\033[0m (expected \033[33m0\033[0m)", cases[i].label, got);
	}
}
