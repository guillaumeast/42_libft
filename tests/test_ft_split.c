#include <criterion/criterion.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"

typedef struct {
	const char	*input;
	char		sep;
	const char	**expected;
	const char	*label;
}	t_case;

static void	check_split_result(char **got, const char **expected, const char *label)
{
	size_t	i = 0;

	if (!expected) {
		cr_expect_eq(got, NULL,
			"\033[31mft_split(%s)\033[0m = \033[33mnon-NULL\033[0m (expected \033[33mNULL\033[0m)", label);
		return;
	}

	cr_expect_neq(got, NULL,
		"\033[31mft_split(%s)\033[0m = \033[33mNULL\033[0m (expected \033[33mvalid array\033[0m)", label);

	if (!got)
		return;

	while (expected[i]) {
		cr_expect_neq(got[i], NULL,
			"\033[31mft_split(%s)[%zu]\033[0m = \033[33mNULL\033[0m (expected \033[33m\"%s\"\033[0m)", label, i, expected[i]);

		if (got[i])
			cr_expect_str_eq(got[i], expected[i],
				"\033[31mft_split(%s)[%zu]\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				label, i, got[i], expected[i]);
		i++;
	}

	cr_expect_eq(got[i], NULL,
		"\033[31mft_split(%s)\033[0m result not \033[33mNULL-terminated\033[0m (expected \033[33mNULL terminator\033[0m)", label);

	/* free result */
	for (size_t j = 0; got[j]; j++)
		free(got[j]);
	free(got);
}

Test(ft_split, full_tests)
{
	const char *exp1[] = {"hello", "world", NULL};
	const char *exp2[] = {"42", "Network", NULL};
	const char *exp3[] = {"abc", "def", "ghi", NULL};
	const char *exp4[] = {"one", NULL};
	const char *exp5[] = {NULL};
	const char *exp6[] = {"split", "with", "  ", "spaces", NULL};
	const char *exp7[] = {NULL};

	const t_case cases[] = {
		// Basic split
		{"hello world", ' ', exp1, "\"hello world\", \' \'"},

		// Multiple separators
		{"42-Network", '-', exp2, "\"42-Network\", \'-\'"},

		// Repeated separators
		{"abc--def--ghi", '-', exp3, "\"abc--def--ghi\", \'-\'"},

		// Trailing separator
		{"one-", '-', exp4, "\"one-\", \'-\'"},

		// Only separator
		{"-", '-', exp5, "\"-\", \'-\'"},

		// Mixed characters
		{"split,with,  ,spaces", ',', exp6, "\"split,with,  ,spaces\", \',\'"},

		// Empty string
		{"", ',', exp7, """, ','"},

		// No occurrence of separator
		{"nosplit", ',', (const char *[]){"nosplit", NULL}, "\"nosplit\", \',\'"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char **got = ft_split(cases[i].input, cases[i].sep);
		check_split_result(got, cases[i].expected, cases[i].label);
	}
}
