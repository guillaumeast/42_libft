#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	const char	*input;
	size_t		expected_output;
	const char	*label;
}	t_case;

Test(ft_strlen, full_tests)
{
	const t_case cases[] = {
		// Basic strings (ASCII)
		{"", 0, "\"\" (empty string)"},
		{"a", 1, "\"a\""},
		{"42", 2, "\"42\""},
		{"Hello", 5, "\"Hello\""},

		// Strings with spaces and punctuation
		{"Hello world!", 12, "\"Hello world!\""},
		{"This is a test.", 15, "\"This is a test.\""},

		// Strings with escape sequences
		{"Line1\nLine2", 11, "\"Line1\\nLine2\""},
		{"Tab\tSeparated", 13, "\"Tab\\tSeparated\""},

		// UTF-8 (multibyte): strlen counts bytes, not glyphs
		{"éàù", 6, "\"éàù\""},

		// Long string
		{"abcdefghijklmnopqrstuvwxyz", 26, "\"alphabet\""}
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		size_t got = ft_strlen(cases[i].input);
		cr_expect_eq(got, cases[i].expected_output,
			"\033[31mft_strlen(%s)\033[0m = \033[33m%zu\033[0m (expected \033[33m%zu\033[0m)",
			cases[i].label, got, cases[i].expected_output);
	}
}
