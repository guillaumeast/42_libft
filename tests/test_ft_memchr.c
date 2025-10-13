#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	const char	*input;
	int			search;
	size_t		n;
	const char	*expected_result;
	const char	*label;
}	t_case;

Test(ft_memchr, full_tests)
{
	const t_case cases[] = {
		// byte present before n
		{"abcdef", 'c', 6, "cdef", "found within range"},

		// byte at very end of range
		{"abcdef", 'f', 6, "f", "found at last byte"},

		// byte outside n (should not be found)
		{"abcdef", 'f', 5, NULL, "not found (out of range)"},

		// byte not present at all
		{"abcdef", 'x', 6, NULL, "not found"},

		// search for NUL byte
		{"abc\0def", '\0', 7, "\0def", "NUL byte"},

		// n = 0 -> always NULL
		{"abcdef", 'a', 0, NULL, "n=0"},

		// empty string (n > 0)
		{"", 'a', 5, NULL, "empty string"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		const void *got = ft_memchr(cases[i].input, cases[i].search, cases[i].n);

		if (cases[i].expected_result == NULL) {
			cr_expect_eq(got, NULL,
				"\033[31mft_memchr(\"%s\", \'%c\', %zu)\033[0m = \033[33mnon-NULL\033[0m (expected \033[33mNULL\033[0m)",
				cases[i].input, cases[i].search, cases[i].n);
		} else {
			cr_expect_str_eq(got, cases[i].expected_result,
				"\033[31mft_memchr(\"%s\", \'%c\', %zu)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].input, cases[i].search, cases[i].n, (const char *)got, cases[i].expected_result);
		}
	}
}
