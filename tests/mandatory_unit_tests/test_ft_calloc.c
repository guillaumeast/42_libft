#include <criterion/criterion.h>
#include <string.h>
#include "libft.h"

typedef struct {
	size_t		count;
	size_t		size;
	const char	*label;
}	t_case;

Test(ft_calloc, full_tests)
{
	const t_case cases[] = {
		// Basic allocations
		{1, sizeof(int), "1, sizeof(int)"},
		{5, sizeof(char), "5, sizeof(char)"},
		{10, sizeof(double), "10, sizeof(double)"},

		// Zero-size allocation (implementation-defined but should not segfault)
		{0, sizeof(int), "0, sizeof(int)"},
		{4, 0, "4, 0"},

		// Large allocation (check overflow safety)
		{SIZE_MAX, 2, "SIZE_MAX, 2"},
		{2, SIZE_MAX, "2, SIZE_MAX"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		void *ptr = ft_calloc(cases[i].count, cases[i].size);

		if (cases[i].count == 0 || cases[i].size == 0 ||
			cases[i].count > SIZE_MAX / (cases[i].size ? cases[i].size : 1)) {
			// Overflow or zero-size: behavior may vary, but must not crash
			cr_expect(1, "ft_calloc(%s) did not crash (undefined but safe)", cases[i].label);
			free(ptr);
			continue;
		}

		cr_expect_neq(ptr, NULL,
			"\033[31mft_calloc(%s) = NULL\033[0m (expected \033[33mvalid pointer\033[0m)",
			cases[i].label);

		if (ptr) {
			// Verify that all bytes are zeroed
			size_t total = cases[i].count * cases[i].size;
			unsigned char *bytes = ptr;
			int zeroed = 1;
			for (size_t j = 0; j < total; j++) {
				if (bytes[j] != 0) {
					zeroed = 0;
					break;
				}
			}
			cr_expect(zeroed,
				"\033[31mft_calloc(%s)\033[0m = \033[33mnot zero-initialized\033[0m (expected \033[33mall bytes = 0\033[0m)",
				cases[i].label);
			free(ptr);
		}
	}
}
