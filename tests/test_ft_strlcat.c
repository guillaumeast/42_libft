#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	const char	*dst_init;
	const char	*src;
	size_t		dstsize;
	size_t		expected_return;
	const char	*expected_result;
	const char	*label;
}	t_case;

Test(ft_strlcat, full_tests)
{
	const t_case cases[] = {
		// Normal concatenation (enough space)
		{"Hello", "World", 12, 10, "HelloWorld", "normal concatenation"},

		// Truncation: not enough space to append fully
		{"Hello", "World", 8, 10, "HelloWo", "truncated concatenation"},

		// dstsize = 0 -> nothing copied, return strlen(src)
		{"Hello", "World", 0, 5, "Hello", "dstsize=0 no-op"},

		// dst longer than dstsize -> should return dstsize + strlen(src)
		{"HelloWorld", "42", 5, 7, "HelloWorld", "dst longer than dstsize"},

		// empty src
		{"Hello", "", 10, 5, "Hello", "empty src"},

		// empty dst
		{"", "Hello", 10, 5, "Hello", "empty dst"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char	dst[64];
		char	expected[64];

		memset(dst, 0, sizeof(dst));
		memset(expected, 0, sizeof(expected));

		strcpy(dst, cases[i].dst_init);
		strcpy(expected, cases[i].expected_result);

		size_t ret = ft_strlcat(dst, cases[i].src, cases[i].dstsize);

		cr_expect_eq(ret, cases[i].expected_return,
			"\033[31mft_strlcat(\"%s\", \"%s\", %zu)\033[0m = \033[33m%zu\033[0m (expected \033[33m%zu\033[0m)",
			dst, cases[i].src, cases[i].dstsize, ret, cases[i].expected_return);

		cr_expect_str_eq(dst, expected,
			"\033[31mft_strlcat(\"%s\", \"%s\", %zu)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
			dst, cases[i].src, cases[i].dstsize, dst, expected);
	}
}
