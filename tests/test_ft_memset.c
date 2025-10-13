#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	size_t		buf_size;
	int			fill;
	size_t		len;
	const char	*label;
}	t_case;

static void	init_pattern(unsigned char *buf, size_t n)
{
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char)('a' + (i % 26));
}

Test(ft_memset, full_tests)
{
	const t_case cases[] = {
		// No-op: len = 0 (buffer must remain unchanged, return == dst)
		{16, 'X', 0, "len=0 no-op"},

		// Partial fill: first 5 bytes replaced
		{16, 'A', 5, "partial fill 5"},

		// Full fill: all bytes set to NUL
		{16, 0, 16, "fill NULs"},

		// Cast behavior: -1 -> 255
		{16, -1, 8, "fill -1 -> 255"},

		// Cast behavior: 300 -> 44
		{16, 300, 7, "fill 300 -> 44"},

		// Edge: single byte buffer
		{1, 'Z', 1, "single byte"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		unsigned char	buf[64];
		unsigned char	expected[64];

		cr_assert(cases[i].buf_size <= sizeof(buf),
			"Test harness: buf_size too big");

		/* start from the same known pattern */
		init_pattern(buf, cases[i].buf_size);
		init_pattern(expected, cases[i].buf_size);

		/* build expected content manually (no libc dependency) */
		for (size_t j = 0; j < cases[i].len && j < cases[i].buf_size; j++)
			expected[j] = (unsigned char)cases[i].fill;

		/* call function under test */
		void *ret = ft_memset(buf, cases[i].fill, cases[i].len);

		/* check return pointer */
		cr_expect_eq(ret, (void *)buf,
			"\033[31mft_memset(\"%s\")\033[0m = \033[33m%p\033[0m (expected \033[33m%p\033[0m)",
			cases[i].label, ret, (void *)buf);

		/* check bytes written are exactly as expected across the whole buffer */
		int diff = memcmp(buf, expected, cases[i].buf_size);
		cr_expect_eq(diff, 0,
			"\033[31mft_memset(\"%s\")\033[0m wrote \033[33munexpected bytes\033[0m (expected \033[33mexact match\033[0m)",
			cases[i].label);
	}
}
