#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	size_t		len;
	const char	*label;
}	t_case;

static void	init_pattern(unsigned char *buf, size_t n)
{
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char)('a' + (i % 26));
}

Test(ft_memmove, full_tests)
{
	const t_case cases[] = {
		// len = 0 -> no-op
		{0, "len=0 no-op"},

		// non-overlapping copy
		{8, "non-overlapping 8"},

		// overlapping (dst < src)
		{10, "overlap dst<src"},

		// overlapping (dst > src)
		{10, "overlap dst>src"},

		// full buffer
		{26, "copy 26 (alphabet)"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		unsigned char	buf[64];
		unsigned char	expected[64];

		init_pattern(buf, sizeof(buf));
		init_pattern(expected, sizeof(expected));

		if (strcmp(cases[i].label, "overlap dst<src") == 0) {
			memmove(expected, expected + 5, cases[i].len);
			ft_memmove(buf, buf + 5, cases[i].len);
		} else if (strcmp(cases[i].label, "overlap dst>src") == 0) {
			memmove(expected + 5, expected, cases[i].len);
			ft_memmove(buf + 5, buf, cases[i].len);
		} else {
			memmove(expected, expected + 32, cases[i].len);
			ft_memmove(buf, buf + 32, cases[i].len);
		}

		int diff = memcmp(buf, expected, sizeof(buf));
		cr_expect_eq(diff, 0,
			"\033[31mft_memmove(\"%s\")\033[0m produced \033[33munexpected bytes\033[0m (expected \033[33mexact match\033[0m)",
			cases[i].label);
	}
}
