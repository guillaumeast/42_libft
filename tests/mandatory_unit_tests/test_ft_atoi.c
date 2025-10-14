#include <criterion/criterion.h>
#include <limits.h>
#include "libft.h"

typedef struct {
	const char	*input;
	int			expected_output;
	const char	*label;
}	t_case;

Test(ft_atoi, full_tests)
{
	const t_case cases[] = {
		// basic numbers
		{"0", 0, "\"0\""},
		{"42", 42, "\"42\""},
		{"-42", -42, "\"-42\""},
		{"+42", 42, "\"+42\""},

		// leading whitespace (space, \t, \n, \v, \f, \r)
		{"   123", 123, "\"   123\""},
		{"\t\n  456", 456, "\"\\t\\n  456\""},
		{"\v\f\r7", 7, "\"\\v\\f\\r7\""},

		// leading zeros
		{"+00123", 123, "\"+00123\""},

		// stops at first non-digit after having parsed some digits
		{"123abc", 123, "\"123abc\""},

		// non-digit first (no digits parsed) -> 0
		{"abc123", 0, "\"abc123\""},

		// sign without following digits -> 0
		{"+", 0, "\"+\""},
		{"-", 0, "\"-\""},

		// multiple signs / invalid sign sequences -> 0
		{"--5", 0, "\"--5\""},
		{"+-5", 0, "\"+-5\""},
		{"-+5", 0, "\"-+5\""},

		// int limits (implementation-defined if overflow; we only test exact limits)
		{"2147483647", INT_MAX, "\"INT_MAX\""},
		{"-2147483648", INT_MIN, "\"INT_MIN\""},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got = ft_atoi(cases[i].input);
		cr_expect_eq(got, cases[i].expected_output,
			"\033[31mft_atoi(%s)\033[0m = \033[33m%d\033[0m (expected \033[33m%d\033[0m)",
			cases[i].label, got, cases[i].expected_output);
	}
}
