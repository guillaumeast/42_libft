#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
	const char	*haystack;
	const char	*needle;
	size_t		len;
	const char	*expected_result; // NULL if not found
	const char	*label;
}	t_case;

Test(ft_strnstr, full_tests)
{
	const t_case cases[] = {
		// Empty needle -> return haystack (even if len == 0)
		{"Hello", "", 0, "Hello", "empty needle, len=0"},
		{"Hello", "", 3, "Hello", "empty needle, len=3"},

		// Found fully within len
		{"foobar", "oba", 6, "obar", "found in middle"},
		{"abcabc", "abc", 6, "abcabc", "first occurrence"},

		// Found at the very end boundary (needle fits exactly before len)
		{"abcde", "de", 5, "de", "found at end boundary"},

		// Not found because len too small to fit the whole needle
		{"abcde", "de", 4, NULL, "not found (cut by len)"},
		{"foobar", "bar", 5, NULL, "not found (len excludes match)"},

		// Needle longer than haystack (within given len)
		{"abc", "abcd", 4, NULL, "needle longer than haystack"},

		// Not found at all
		{"hello", "world", 5, NULL, "not found"},

		// len bigger than haystack length (should still behave correctly)
		{"hello", "lo", 999, "lo", "len > haystack"},

		// haystack empty
		{"", "", 10, "", "empty haystack & empty needle"},
		{"", "a", 10, NULL, "empty haystack, non-empty needle"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		const char *got = ft_strnstr(cases[i].haystack, cases[i].needle, cases[i].len);

		if (cases[i].expected_result == NULL) {
			cr_expect_eq(got, NULL,
				"\033[31mft_strnstr(\"%s\", \"%s\", %zu)\033[0m = \033[33mnon-NULL\033[0m (expected \033[33mNULL\033[0m)",
				cases[i].haystack, cases[i].needle, cases[i].len);
		} else {
			cr_expect_str_eq(got, cases[i].expected_result,
				"\033[31mft_strnstr(\"%s\", \"%s\", %zu)\033[33m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].haystack, cases[i].needle, cases[i].len,
				(got ? got : "(null)"), cases[i].expected_result);
		}
	}
}
