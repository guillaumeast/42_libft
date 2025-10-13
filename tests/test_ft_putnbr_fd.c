#include <criterion/criterion.h>
#include "libft.h"
#include <unistd.h>   // pipe, read, close
#include <string.h>   // strlen
#include <limits.h>   // INT_MAX, INT_MIN
#include <stdio.h>    // snprintf

typedef struct {
	int			n;
	const char	*expected;
	const char	*label; // ex: "42, fd"
}	t_case;

static void	check_putnbr_fd(int n, const char *expected, const char *label)
{
	int fds[2];
	cr_assert_eq(pipe(fds), 0, "pipe() failed");

	ft_putnbr_fd(n, fds[1]);
	close(fds[1]);

	char	buf[128];
	ssize_t	total = read(fds[0], buf, sizeof(buf) - 1);
	close(fds[0]);
	if (total < 0)
		total = 0;
	buf[total] = '\0';

	size_t exp_len = strlen(expected);

	cr_expect_eq((size_t)total, exp_len,
		"\033[31mft_putnbr_fd(%s)\033[0m = \033[33m%zd bytes\033[0m (expected \033[33m%zu\033[0m)",
		label, total, exp_len);

	cr_expect_str_eq(buf, expected,
		"\033[31mft_putnbr_fd(%s)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
		label, buf, expected);
}

Test(ft_putnbr_fd, full_tests)
{
	const t_case cases[] = {
		{0, "0", "0, fd"},
		{1, "1", "1, fd"},
		{-1, "-1", "-1, fd"},
		{42, "42", "42, fd"},
		{-42, "-42", "-42, fd"},
		{12345, "12345", "12345, fd"},
		{-12345, "-12345", "-12345, fd"},
		{INT_MAX, "2147483647", "INT_MAX, fd"},
		{INT_MIN, "-2147483648", "INT_MIN, fd"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		check_putnbr_fd(cases[i].n, cases[i].expected, cases[i].label);
	}
}
