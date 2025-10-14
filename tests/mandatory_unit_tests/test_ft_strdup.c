#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	const char	*input;
	const char	*label;
}	t_case;

Test(ft_strdup, full_tests)
{
	const t_case cases[] = {
		// Basic strings
		{"Hello", "\"Hello\""},
		{"42", "\"42\""},
		{"", "\"\""},

		// Strings with spaces and punctuation
		{"Hello world!", "\"Hello world!\""},
		{"This is a test.", "\"This is a test.\""},

		// Strings with escape sequences
		{"Line1\nLine2", "\"Line1\\nLine2\""},
		{"Tab\tSeparated", "\"Tab\\tSeparated\""},

		// Extended ASCII / UTF-8
		{"éàù", "\"éàù\""},

		// Longer string
		{"abcdefghijklmnopqrstuvwxyz", "\"alphabet\""},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char *dup = ft_strdup(cases[i].input);

		cr_expect_neq(dup, NULL,
			"\033[31mft_strdup(%s)\033[0m = \033[33mNULL\033[0m (expected \033[33mvalid pointer\033[0m)",
			cases[i].label);

		if (dup) {
			cr_expect_str_eq(dup, cases[i].input,
				"\033[31mft_strdup(%s)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].label, dup, cases[i].input);

			// Verify deep copy (not the same address)
			cr_expect_neq(dup, cases[i].input,
				"\033[31mft_strdup(%s)\033[0m = \033[33mpointer to original string\033[0m (expected \033[33mindependent copy\033[0m)",
				cases[i].label);

			free(dup);
		}
	}
}
