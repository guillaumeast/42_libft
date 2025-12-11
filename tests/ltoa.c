#include "fut.h"
#include "libft.h"
#include <limits.h>
#include <stdio.h>

static void	test_ft_itoa(int n, const char *expected)
{
	char	*result;

	result = ft_itoa(n);
	assert_eq(RET, 0, result, expected);
	free(result);
}

static void	test_ft_utoa(unsigned int n, const char *expected)
{
	char	*result;

	result = ft_utoa(n);
	assert_eq(RET, 0, result, expected);
	free(result);
}

static void	test_ft_ltoa(long n, const char *expected)
{
	char	*result;

	result = ft_ltoa(n);
	assert_eq(RET, 0, result, expected);
	free(result);
}

Test(test_itoa, 1)
{
	test_ft_itoa(0, "0");
	test_ft_itoa(-0, "0");
	test_ft_itoa(+0, "0");
	test_ft_itoa(-1, "-1");
	test_ft_itoa(42, "42");
	test_ft_itoa(INT_MIN, "-2147483648");
	test_ft_itoa(INT_MAX, "2147483647");
}

Test(test_utoa, 1)
{
	test_ft_utoa(0, "0");
	test_ft_utoa(-0, "0");
	test_ft_utoa(+0, "0");
	test_ft_utoa(42, "42");
	test_ft_utoa(INT_MAX, "2147483647");
	test_ft_utoa(UINT_MAX, "4294967295");
}

Test(test_ltoa, 1)
{
	test_ft_ltoa(0, "0");
	test_ft_ltoa(-0, "0");
	test_ft_ltoa(+0, "0");
	test_ft_ltoa(-1, "-1");
	test_ft_ltoa(42, "42");
	test_ft_ltoa(LONG_MIN, "-9223372036854775808");
	test_ft_ltoa(INT_MIN, "-2147483648");
	test_ft_ltoa(INT_MAX, "2147483647");
	test_ft_ltoa(UINT_MAX, "4294967295");
	test_ft_ltoa(LONG_MAX, "9223372036854775807");
}
