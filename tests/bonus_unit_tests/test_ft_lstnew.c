#include <criterion/criterion.h>
#include "libft.h"
#include <string.h>

typedef struct {
	void		*content;
	const char	*label;   // ex: "\"hello\"" or "malloced \"abc\""
	int			needs_free;
}	t_case;

Test(ft_lstnew, full_tests)
{
	char *heap_str = malloc(4);
	cr_assert_neq(heap_str, NULL, "malloc failed");
	memcpy(heap_str, "abc", 4); // includes '\0'

	static int	static_num = 42;
	const t_case cases[] = {
		{(void *)"hello", "\"hello\"", 0},
		{heap_str, "malloced \"abc\"", 1},
		{&static_num, "&static_num(42)", 0},
		{NULL, "NULL", 0},
	};

	for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
		t_list *node = ft_lstnew(cases[i].content);

		cr_expect_neq(node, NULL,
			"\033[31mft_lstnew(%s)\033[0m = \033[33mNULL\033[0m (expected \033[33mnon-NULL node\033[0m)",
			cases[i].label);

		if (node) {
			cr_expect_eq(node->content, cases[i].content,
				"\033[31mft_lstnew(%s)->content\033[0m = \033[33m%p\033[0m (expected \033[33m%p\033[0m)",
				cases[i].label, node->content, cases[i].content);

			cr_expect_eq(node->next, NULL,
				"\033[31mft_lstnew(%s)->next\033[0m = \033[33m%p\033[0m (expected \033[33mNULL\033[0m)",
				cases[i].label, (void *)node->next);

			free(node);
		}
	}

	/* cleanup */
	free(heap_str);
}
