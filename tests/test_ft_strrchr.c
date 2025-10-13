#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	const char	*input;
	int			search;
	const char	*expected_result;
	const char	*label;
}	t_case;

Test(ft_strrchr, full_tests)
{
	const t_case cases[] = {
		// character present once
		{"Hello", 'e', "ello", "single occurrence"},

		// character present multiple times (returns last)
		{"banana", 'a', "a", "multiple occurrences"},

		// character at the beginning
		{"42", '4', "42", "first character"},

		// character at the end
		{"Hello", 'o', "o", "last character"},

		// search for NUL terminator
		{"Hello", '\0', "", "NUL terminator"},

		// character not present
		{"Hello", 'x', NULL, "not found"},

		// empty string
		{"", 'a', NULL, "empty string"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		const char *got = ft_strrchr(cases[i].input, cases[i].search);

		if (cases[i].expected_result == NULL) {
			cr_expect_eq(got, NULL,
				"\033[31mft_strrchr(\"%s\", '%c')\033[0m = \033[33mnon-NULL\033[0m (expected \033[33mNULL\033[0m)",
				cases[i].input, cases[i].search);
		} else {
			cr_expect_str_eq(got, cases[i].expected_result,
				"\033[31mft_strrchr(\"%s\", '%c')\033[0m = \033[31m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].input, cases[i].search, got, cases[i].expected_result);
		}
	}
}
