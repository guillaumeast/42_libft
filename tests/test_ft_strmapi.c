#include <criterion/criterion.h>
#include <stdlib.h>
#include "libft.h"

/* mapping functions used for tests */
static char	map_id(unsigned int i, char c) { (void)i; return c; }
static char	map_upper(unsigned int i, char c) { (void)i; return (c >= 'a' && c <= 'z') ? (c - 32) : c; }
static char	map_add_index(unsigned int i, char c) { return (char)(c + (int)i); }
static char	map_altcase(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
		return (i % 2 == 0) ? (c - 32) : c; /* even -> upper */
	if (c >= 'A' && c <= 'Z')
		return (i % 2 == 0) ? c : (c + 32); /* odd -> lower */
	return c;
}
static char	map_plus_one(unsigned int i, char c) { (void)i; return (char)(c + 1); }

typedef struct {
	const char	*input;
	char		(*f)(unsigned int, char);
	const char	*expected;
	const char	*label;   /* textual call for logs, e.g. "\"abc\", upper" */
}	t_case;

Test(ft_strmapi, full_tests)
{
	const t_case cases[] = {
		/* identity */
		{"Hello", map_id, "Hello", "\"Hello\", id"},

		/* to upper */
		{"abcZ", map_upper, "ABCZ", "\"abcZ\", upper"},

		/* add index: "aaaaa" -> 'a'+0..4 => "abcde" */
		{"aaaaa", map_add_index, "abcde", "\"aaaaa\", add_index"},

		/* alternate case by index */
		{"abcdef", map_altcase, "AbCdEf", "\"abcdef\", altcase"},

		/* empty string */
		{"", map_upper, "", "\"\", upper"},

		/* numeric +1 */
		{"01239", map_plus_one, "1234:", "\"01239\", plus_one"},

		/* UTF-8 bytes preserved if map doesn't alter them */
		{"éà", map_id, "éà", "\"éà\", id"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		char *got = ft_strmapi(cases[i].input, cases[i].f);

		cr_expect_neq(got, NULL,
			"\033[31mft_strmapi(%s)\033[0m = \033[33mNULL\033[0m (expected \033[33mallocated string\033[0m)",
			cases[i].label);

		if (got) {
			cr_expect_str_eq(got, cases[i].expected,
				"\033[31mft_strmapi(%s)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
				cases[i].label, got, cases[i].expected);
			free(got);
		}
	}
}
