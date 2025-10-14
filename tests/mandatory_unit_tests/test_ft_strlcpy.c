#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	const char	*src;
	size_t		dstsize;
	size_t		expected_return;
	const char	*expected_result;
	const char	*label;
}	t_case;

Test(ft_strlcpy, full_tests)
{
	const t_case cases[] = {
		// dstsize = 0 -> no copy, return src length
		{"Hello", 0, 5, "unchanged", "dstsize=0 no-op"},

		// dst large enough
		{"Hello", 10, 5, "Hello", "dst large enough"},

		// dst smaller than src
		{"HelloWorld", 6, 10, "Hello", "truncated copy"},

		// empty src
		{"", 5, 0, "", "empty src"},

		// single char
		{"A", 2, 1, "A", "single char"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char	dst[64];
		char	expected[64];

		memset(dst, 'X', sizeof(dst));
		memset(expected, 'X', sizeof(expected));

		if (strcmp(cases[i].expected_result, "unchanged") != 0)
			strcpy(expected, cases[i].expected_result);

		size_t ret = ft_strlcpy(dst, cases[i].src, cases[i].dstsize);

		cr_expect_eq(ret, cases[i].expected_return,
			"\033[31mft_strlcpy(\"%s\", \"%s\", %zu)\033[0m = \033[33m%zu\033[0m (expected \033[33m%zu\033[0m)",
			dst, cases[i].src, cases[i].dstsize, ret, cases[i].expected_return);

		if (cases[i].dstsize > 0) {
			cr_expect_str_eq(dst, expected,
				"\033[31mft_strlcpy(\"%s\", \"%s\", %zu)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				dst, cases[i].src, cases[i].dstsize, dst, expected);
		}
	}
}
