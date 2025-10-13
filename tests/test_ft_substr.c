#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

typedef struct {
	const char	*input;
	unsigned int start;
	size_t		len;
	const char	*expected;
	const char	*label;
}	t_case;

Test(ft_substr, full_tests)
{
	const t_case cases[] = {
		// start=0, len=0 -> empty string
		{"123456789", 0, 0, "", "start=0 len=0"},

		// start=0, len within bounds
		{"123456789", 0, 3, "123", "start=0 len=3"},
		{"hello", 0, 5, "hello", "full copy"},

		// middle slice
		{"123456789", 4, 3, "567", "middle slice 4..6"},
		{"abcdef", 2, 2, "cd", "middle slice 2..3"},

		// len longer than remaining -> clamp to end
		{"123456789", 6, 99, "789", "len exceeds end"},

		// start exactly at end -> empty string
		{"hello", 5, 10, "", "start==strlen -> empty"},

		// start beyond end -> empty string
		{"hello", 42, 3, "", "start>strlen -> empty"},

		// with spaces and punctuation
		{"Hi there!", 3, 5, "there", "slice with space"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char *got = ft_substr(cases[i].input, cases[i].start, cases[i].len);

		cr_expect_neq(got, NULL,
			"\033[31mft_substr(\"%s\", %u, %zu)\033[0m = \033[33mNULL\033[0m (expected \033[33mallocated string\033[0m)",
			cases[i].input, cases[i].start, cases[i].len);

		if (got) {
			cr_expect_str_eq(got, cases[i].expected,
				"\033[31mft_substr(\"%s\", %u, %zu)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].input, cases[i].start, cases[i].len, got, cases[i].expected);

			/* deep copy: result must not point inside string literal storage */
			if (cases[i].expected[0] != '\0') {
				cr_expect_neq(got, cases[i].input + cases[i].start,
					"\033[31mft_substr(\"%s\", %u, %zu)\033[0m = \033[33mpointer into the original buffer\033[0m (expected \033[33mindependent allocation\033[0m)",
					cases[i].input, cases[i].start, cases[i].len);
			}
			free(got);
		}
	}
}
