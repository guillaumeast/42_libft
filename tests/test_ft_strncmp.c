#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	const char	*s1;
	const char	*s2;
	size_t		n;
	int			expected_sign; // -1 if s1<s2, 0 if equal, 1 if s1>s2
	const char	*label;
}	t_case;

static int	sign(int v)
{
	return (v > 0) - (v < 0);
}

Test(ft_strncmp, full_tests)
{
	const t_case cases[] = {
		// n = 0 -> always equal
		{"abc", "xyz", 0, 0, "n=0"},

		// identical strings
		{"hello", "hello", 5, 0, "equal full"},
		{"hello", "hello", 10, 0, "equal beyond length"},

		// equal up to n, then differ afterwards -> result must be 0
		{"foobar", "fooBAR", 3, 0, "equal first 3"},

		// differ within first n
		{"abc", "abd", 3, -1, "diff at pos 3 (c<d)"},
		{"abd", "abc", 3, 1, "diff at pos 3 (d>c)"},

		// one string is prefix of the other
		{"abc", "abcd", 4, -1, "prefix shorter < longer (n=4)"},
		{"abcd", "abc", 4, 1, "longer > shorter (n=4)"},
		{"abc", "abcd", 3, 0, "prefix equal when n=3"},

		// empty strings
		{"", "", 5, 0, "both empty"},
		{"", "a", 1, -1, "empty < non-empty"},
		{"a", "", 1, 1, "non-empty > empty"},

		// different case same letters
		{"Apple", "apple", 5, -1, "A(65) < a(97)"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got_raw = ft_strncmp(cases[i].s1, cases[i].s2, cases[i].n);
		int got = sign(got_raw);
		cr_expect_eq(got, cases[i].expected_sign,
			"\033[31mft_strncmp(\"%s\", \"%s\", %zu)\033[0m = \033[33m%d\033[0m (expected \033[33m%d\033[0m)",
			cases[i].s1, cases[i].s2, cases[i].n, got, cases[i].expected_sign);
	}
}
