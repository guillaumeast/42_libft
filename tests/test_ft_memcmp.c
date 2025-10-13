#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	const void	*s1;
	const void	*s2;
	size_t		n;
	int			expected_sign; // -1 if s1<s2, 0 if equal, 1 if s1>s2
	const char	*label;
}	t_case;

static int	sign(int v)
{
	return (v > 0) - (v < 0);
}

Test(ft_memcmp, full_tests)
{
	const t_case cases[] = {
		// n = 0 -> always equal
		{"abc", "xyz", 0, 0, "n=0"},

		// identical memory
		{"abcdef", "abcdef", 6, 0, "identical"},

		// differ at first byte
		{"abc", "xbc", 3, -1, "diff at first byte"},

		// differ later
		{"abcd", "abzd", 4, -1, "diff at 3rd byte (c<z)"},

		// one shorter, but n limits comparison
		{"abc", "abcd", 3, 0, "equal for first 3"},
		{"abc", "abd", 3, -1, "diff within n"},

		// binary data including null bytes
		{"ab\0cd", "ab\0cd", 5, 0, "identical with NUL"},
		{"ab\0cd", "ab\0cD", 5, 1, "diff after NUL"},

		// empty
		{"", "", 1, 0, "empty strings"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		int got_raw = ft_memcmp(cases[i].s1, cases[i].s2, cases[i].n);
		int got = sign(got_raw);
		cr_expect_eq(got, cases[i].expected_sign,
			"\033[31mft_memcmp(\"%s\", \"%s\", %zu)\033[0m = \033[33m%d\033[0m (expected \033[33m%d\033[0m)",
			(const char *)cases[i].s1, (const char *)cases[i].s2,
			cases[i].n, got, cases[i].expected_sign);
	}
}
