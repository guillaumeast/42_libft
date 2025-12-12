#include "fut.h"
#include "libft.h"
#include <limits.h>

static void	test_ft_ultoa_base(unsigned long n, const char *base, const char *expected)
{
	char	*result;

	result = ft_ultoa_base(n, base);
	assert_eq(RET, 1, result, expected);
	free(result);
}

Test(test_ultoa_base, 0)
{
	test_ft_ultoa_base(0, "0123456789", "0");
	test_ft_ultoa_base(1, "0123456789", "1");
	test_ft_ultoa_base(42, "0123456789", "42");
	test_ft_ultoa_base(ULONG_MAX, "0123456789", "18446744073709551615");

	test_ft_ultoa_base(0, "0123456789abcdef", "0");
	test_ft_ultoa_base(255, "0123456789abcdef", "ff");
	test_ft_ultoa_base(ULONG_MAX, "0123456789ABCDEF", "FFFFFFFFFFFFFFFF");
	test_ft_ultoa_base(3735928559UL, "0123456789ABCDEF", "DEADBEEF");

	test_ft_ultoa_base(0, "01", "0");
	test_ft_ultoa_base(1, "01", "1");
	test_ft_ultoa_base(5, "01", "101");
	test_ft_ultoa_base(ULONG_MAX, "01", "1111111111111111111111111111111111111111111111111111111111111111");

	assert_eq(RET, 0, ft_ultoa_base(10, ""), NULL);
	assert_eq(RET, 0, ft_ultoa_base(10, "0"), NULL);
	assert_eq(RET, 0, ft_ultoa_base(10, NULL), NULL);
}
