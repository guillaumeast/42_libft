#include <criterion/criterion.h>
#include "libft.h"
#include <unistd.h>   // pipe, read, close
#include <string.h>   // strlen

typedef struct {
	char		c;
	const char	*expected;
	const char	*label;   // ex: "'A', fd"
}	t_case;

static void	check_putchar_fd(char c, const char *expected, const char *label)
{
	int fds[2];
	cr_assert_eq(pipe(fds), 0, "pipe() failed");

	// écrire sur l'extrémité écriture du pipe (sert d'fd)
	ft_putchar_fd(c, fds[1]);
	close(fds[1]);

	char buf[8] = {0};
	ssize_t n = read(fds[0], buf, sizeof(buf) - 1);
	close(fds[0]);

	size_t exp_len = strlen(expected);

	cr_expect_eq((size_t)(n < 0 ? 0 : n), exp_len,
		"\033[31mft_putchar_fd(%s)\033[0m = \033[33m%zd bytes\033[0m (expected \033[33m%zu\033[0m)",
		label, n, exp_len);

	if (n >= 0) {
		cr_expect_arr_eq(buf, expected, exp_len,
			"\033[31mft_putchar_fd(%s)\033[0m = \033[33m\"%.*s\"\033[0m (expected \033[33m\"%s\"\033[0m)",
			label, (int)exp_len, buf, expected);
	}
}

Test(ft_putchar_fd, full_tests)
{
	const t_case cases[] = {
		{'A', "A", "'A', fd"},
		{'z', "z", "'z', fd"},
		{'\n', "\n", "'\\n', fd"},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		check_putchar_fd(cases[i].c, cases[i].expected, cases[i].label);
	}
}
