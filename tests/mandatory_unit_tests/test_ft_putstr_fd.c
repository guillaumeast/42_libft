#include <criterion/criterion.h>
#include "libft.h"
#include <unistd.h>   // pipe, read, close
#include <string.h>   // strlen

typedef struct {
	const char	*s;
	const char	*expected;
	const char	*label;   // ex: "\"hello\", fd"
}	t_case;

static void	check_putstr_fd(const char *s, const char *expected, const char *label)
{
	int fds[2];
	cr_assert_eq(pipe(fds), 0, "pipe() failed");

	ft_putstr_fd((char *)s, fds[1]);
	close(fds[1]);

	char	buf[1024];
	ssize_t	total = 0, r;
	while ((r = read(fds[0], buf + total, (ssize_t)sizeof(buf) - total - 1)) > 0)
		total += r;
	if (total >= 0)
		buf[(total < (ssize_t)sizeof(buf)) ? total : (ssize_t)sizeof(buf) - 1] = '\0';
	close(fds[0]);

	size_t exp_len = strlen(expected);

	cr_expect_eq((size_t)(total < 0 ? 0 : total), exp_len,
		"\033[31mft_putstr_fd(%s)\033[0m = \033[33m%zd bytes\033[0m (expected \033[33m%zu\033[0m)",
		label, total, exp_len);

	if (total >= 0 && exp_len > 0) {
		cr_expect_arr_eq(buf, expected, exp_len,
			"\033[31mft_putstr_fd(%s)\033[0m = \033[33m\"%.*s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
			label, (int)exp_len, buf, expected);
	}
}

Test(ft_putstr_fd, full_tests)
{
	const t_case cases[] = {
		{"Hello", "Hello", "\"Hello\", fd"},
		{"", "", "\"\", fd"},
		{"Line1\nLine2", "Line1\nLine2", "\"Line1\\nLine2\", fd"},
		{" world", " world", "\" world\", fd"},
		// NULL input should not crash and should write nothing (common libft behavior)
		{NULL, "", "NULL, fd"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		check_putstr_fd(cases[i].s, cases[i].expected, cases[i].label);
	}
}
