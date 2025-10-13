#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	size_t		buf_size;
	size_t		len;
	const char	*label;
}	t_case;

static void	init_pattern(unsigned char *buf, size_t n)
{
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char)('a' + (i % 26));
}

Test(ft_bzero, full_tests)
{
	const t_case cases[] = {
		// len = 0 -> no-op
		{16, 0, "len=0 no-op"},

		// partial zeroing
		{16, 5, "partial zero 5"},

		// full zeroing
		{16, 16, "full zero"},

		// buffer of size 1
		{1, 1, "single byte"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		unsigned char	buf[64];
		unsigned char	expected[64];

		cr_assert(cases[i].buf_size <= sizeof(buf),
			"Test harness: buf_size too big");

		/* initialize pattern */
		init_pattern(buf, cases[i].buf_size);
		init_pattern(expected, cases[i].buf_size);

		/* zero expected area manually */
		for (size_t j = 0; j < cases[i].len && j < cases[i].buf_size; j++)
			expected[j] = 0;

		/* call function under test */
		ft_bzero(buf, cases[i].len);

		/* compare entire buffer */
		int diff = memcmp(buf, expected, cases[i].buf_size);
		cr_expect_eq(diff, 0,
			"\033[31mft_bzero(buf, %zu)\033[0m = \033[33m%d\033[0m (expected \033[33m0\033[0m)",
			cases[i].len, diff);
	}
}
