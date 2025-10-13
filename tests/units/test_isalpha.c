#include <criterion/criterion.h>
#include "libft.h"

typedef struct {
    int			tested_char;
    int			expected_output;
    const char	*label;
}	t_case;

Test(ft_isalpha, full_tests)
{
    const t_case cases[] = {
        {'A', 1, "A"},
        {'M', 1, "M"},
        {'Z', 1, "Z"},
        {'a', 1, "a"},
        {'m', 1, "m"},
        {'z', 1, "z"},

        {'@', 0, "@"},
        {'[', 0, "["},
        {'`', 0, "`"},
        {'{', 0, "{"},

        {'0', 0, "0"},
        {'9', 0, "9"},
        {' ', 0, " "},
        {'\n',0, "\\n"},
        {'\0',0, "\\0"},

        {-32, 0, "-32"},
        {127, 0, "DEL"},
        {233, 0, "é"},
    };

    for (size_t i = 0; i < sizeof(cases)/sizeof(cases[0]); i++) {
        int got = ft_isalpha(cases[i].tested_char);
        if (cases[i].expected_output)
            cr_expect_neq(got, 0, "\033[31mft_isalpha(\"%s\") = \033[31m%d\033[0m (expected \033[33mnon-zero)\033[0m", cases[i].label, got);
        else
            cr_expect_eq (got, 0, "\033[31mft_isalpha(\"%s\") = \033[31m%d\033[0m (expected \033[33m0)\033[0m", cases[i].label, got);
    }
}
