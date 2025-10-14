#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	const char	*s1;
	const char	*set;
	const char	*expected;
	const char	*label;
}	t_case;

Test(ft_strtrim, full_tests)
{
	const t_case cases[] = {
		// basic trims
		{"  hello  ", " ", "hello", "trim spaces"},
		{"\t\nhello\n\t", "\n\t", "hello", "trim tabs and newlines"},
		{"xx42xx", "x", "42", "trim x"},

		// no characters to trim
		{"hello", " ", "hello", "no trim needed"},

		// set includes all characters
		{"xxxxx", "x", "", "trim all"},

		// set partially overlaps
		{"abcXYZcba", "abc", "XYZ", "trim symmetrical chars"},

		// empty input
		{"", " ", "", "empty string"},

		// empty set -> nothing removed
		{"   spaced   ", "", "   spaced   ", "empty set"},

		// input equals set
		{"aaa", "a", "", "input fully trimmed"},

		// Unicode-like bytes (no matching in set)
		{"éàù", "a", "éàù", "utf8 unchanged"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char *got = ft_strtrim(cases[i].s1, cases[i].set);

		cr_expect_neq(got, NULL,
			"\033[31mft_strtrim(\"%s\", \"%s\")\033[0m = \033[33mNULL\033[0m (expected \033[33mallocated string\033[0m)",
			cases[i].s1, cases[i].set);

		if (got) {
			cr_expect_str_eq(got, cases[i].expected,
				"\033[31mft_strtrim(\"%s\", \"%s\")\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].s1, cases[i].set, got, cases[i].expected);

			cr_expect_neq(got, cases[i].s1,
				"\033[31mft_strtrim(\"%s\", \"%s\")\033[0m = \033[33mpointer to input\033[0m (expected \033[33mindependent copy\033[0m)",
				cases[i].s1, cases[i].set);
			free(got);
		}
	}
}
