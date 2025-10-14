#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

/* mapping functions for testing */
static void	iter_upper(unsigned int i, char *c)
{
	(void)i;
	if (*c >= 'a' && *c <= 'z')
		*c -= 32;
}

static void	iter_add_index(unsigned int i, char *c)
{
	*c = (char)(*c + (int)i);
}

static void	iter_altcase(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z')
		*c = (i % 2 == 0) ? (*c - 32) : *c;
}

typedef struct {
	char		input[64];
	void		(*f)(unsigned int, char *);
	const char	*expected;
	const char	*label;
}	t_case;

Test(ft_striteri, full_tests)
{
	const t_case cases[] = {
		{"hello", iter_upper, "HELLO", "\"hello\", upper"},
		{"abcde", iter_add_index, "acegi", "\"abcde\", add_index"},
		{"abcdef", iter_altcase, "AbCdEf", "\"abcdef\", altcase"},
		{"", iter_upper, "", "\"\", upper"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char buf[64];
		strcpy(buf, cases[i].input);

		ft_striteri(buf, cases[i].f);

		cr_expect_str_eq(buf, cases[i].expected,
			"\033[31mft_striteri(%s)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
			cases[i].label, buf, cases[i].expected);
	}
}
