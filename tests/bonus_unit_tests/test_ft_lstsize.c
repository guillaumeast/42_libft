#include <criterion/criterion.h>
#include "libft.h"

static t_list	*make_node(void *content)
{
	t_list *n = (t_list *)malloc(sizeof(t_list));
	cr_assert_neq(n, NULL, "malloc failed");
	n->content = content;
	n->next = NULL;
	return n;
}

Test(ft_lstsize, full_tests)
{
	/* Case 1: empty list */
	{
		t_list *head = NULL;
		int got = ft_lstsize(head);
		cr_expect_eq(got, 0,
			"\033[31mft_lstsize(NULL)\033[0m = \033[33m%d\033[0m (expected \033[33m0\033[0m)",
			got);
	}

	/* Case 2: one node */
	{
		t_list *a = make_node("a");
		int got = ft_lstsize(a);
		cr_expect_eq(got, 1,
			"\033[31mft_lstsize([a])\033[0m = \033[33m%d\033[0m (expected \033[33m1\033[0m)",
			got);
		free(a);
	}

	/* Case 3: several nodes */
	{
		t_list *a = make_node("a");
		t_list *b = make_node("b");
		t_list *c = make_node("c");
		a->next = b;
		b->next = c;

		int got = ft_lstsize(a);
		cr_expect_eq(got, 3,
			"\033[31mft_lstsize([a->b->c])\033[0m = \033[33m%d\033[0m (expected \033[33m3\033[0m)",
			got);

		free(a); free(b); free(c);
	}
}
