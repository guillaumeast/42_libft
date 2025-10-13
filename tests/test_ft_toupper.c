#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	int			input;
	int			expected_output;
	const char	*label;
}	t_case;

Test(ft_toupper, full_tests)
{
	const t_case cases[] = {
		// lowercase letters -> converted to uppercase
		{'a', 'A', "\'a\'"},
		{'m', 'M', "\'m\'"},
		{'z', 'Z', "\'z\'"},

		// uppercase letters -> unchanged
		{'A', 'A', "\'A\'"},
		{'M', 'M', "\'M\'"},
		{'Z', 'Z', "\'Z\'"},

		// non-alphabetic -> unchanged
		{'0', '0', "\'0\'"},
		{'9', '9', "\'9\'"},
		{' ', ' ', "\' \'"},
		{'@', '@', "\'@\'"},
		{'[', '[', "\'[\'"},

		// out-of-range values -> unchanged
		{-42, -42, "-42"},
		{127, 127, "127"},
		{233, 233, "233"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got = ft_toupper(cases[i].input);
		cr_expect_eq(got, cases[i].expected_output,
			"\033[31mft_toupper(\"%s\")\033[0m = \033[33m%d\033[0m (expected \033[33m%d\033[0m)",
			cases[i].label, got, cases[i].expected_output);
	}
}
