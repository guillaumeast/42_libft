#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

typedef struct {
	const char	*s1;
	const char	*s2;
	const char	*expected;
	const char	*label;
}	t_case;

Test(ft_strjoin, full_tests)
{
	const t_case cases[] = {
		// basic joins
		{"Hello", "World", "HelloWorld", "simple join"},
		{"foo", "bar", "foobar", "foobar"},

		// empty parts
		{"", "", "", "both empty"},
		{"", "abc", "abc", "left empty"},
		{"abc", "", "abc", "right empty"},

		// spaces and punctuation
		{"Hello ", "world!", "Hello world!", "with space"},
		{"[", "]", "[]", "brackets"},

		// repeated / longer
		{"aaaaa", "bbbbb", "aaaaabbbbb", "repeated letters"},

		// UTF-8 (multibyte) — concatenation should preserve bytes
		{"éà", "ù", "éàù", "utf8 join"},

		// mixed content
		{"line1\n", "line2", "line1\nline2", "newline in left"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		const char *s1 = cases[i].s1;
		const char *s2 = cases[i].s2;
		char *got = ft_strjoin(s1, s2);

		cr_expect_neq(got, NULL,
			"\033[31mft_strjoin(\"%s\", \"%s\")\033[0m = \033[33mNULL\033[0m (expected \033[33mallocated string\033[0m)",
			cases[i].s1, cases[i].s2);

		if (got) {
			cr_expect_str_eq(got, cases[i].expected,
				"\033[31mft_strjoin(\"%s\", \"%s\")\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].s1, cases[i].s2, got, cases[i].expected);

			/* length must be strlen(s1)+strlen(s2) */
			size_t expected_len = strlen(s1) + strlen(s2);
			cr_expect_eq(strlen(got), expected_len,
				"\033[31mft_strjoin(\"%s\", \"%s\")\033[0m length = \033[33m%zu\033[0m (expected \033[33m%zu\033[0m)",
				cases[i].s1, cases[i].s2, strlen(got), expected_len);

			/* deep copy: result must not alias inputs */
			cr_expect_neq(got, s1,
				"\033[31mft_strjoin(\"%s\", \"%s\")\033[0m = \033[33mleft input pointer\033[0m (expected \033[33mindependent allocation\033[0m)",
				cases[i].s1, cases[i].s2);
			cr_expect_neq(got, s2,
				"\033[31mft_strjoin(\"%s\", \"%s\")\033[0m = \033[33mright input pointer\033[0m (expected \033[33mindependent allocation\033[0m)",
				cases[i].s1, cases[i].s2);

			free(got);
		}
	}
}
