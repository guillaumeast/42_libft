#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	size_t		size;
	const char	*label;
}	t_case;

static void	init_pattern(unsigned char *buf, size_t n)
{
	for (size_t i = 0; i < n; i++)
		buf[i] = (unsigned char)('a' + (i % 26));
}

Test(ft_memcpy, full_tests)
{
	const t_case cases[] = {
		// len = 0 -> no-op
		{0, "len=0 no-op"},

		// small copy
		{5, "copy 5"},

		// medium copy
		{16, "copy 16"},

		// full buffer
		{26, "copy 26 (alphabet)"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		unsigned char	src[64];
		unsigned char	dst[64];
		unsigned char	expected[64];

		init_pattern(src, sizeof(src));
		memset(dst, 'X', sizeof(dst));
		memset(expected, 'X', sizeof(expected));
		memcpy(expected, src, cases[i].size);

		void *ret = ft_memcpy(dst, src, cases[i].size);

		/* check return pointer */
		cr_expect_eq(ret, (void *)dst,
			"\033[31mft_memcpy(\"%s\", \"%s\", %zu)\033[0m = \033[33m%p\033[0m (expected \033[33m%p\033[0m)",
			dst, expected, sizeof(dst), ret, (void *)dst);

		/* compare buffers */
		int diff = memcmp(dst, expected, sizeof(dst));
		cr_expect_eq(diff, 0,
			"\033[31mft_memcpy(\"%s\", \"%s\", %zu)\033[0m \033[33mwrote unexpected bytes\033[0m (expected \033[33mexact match\033[0m)",
			dst, expected, sizeof(dst));
	}
}
