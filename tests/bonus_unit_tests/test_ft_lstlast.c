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

Test(ft_lstlast, full_tests)
{
	/* Case 1: empty list */
	{
		t_list *head = NULL;
		t_list *got = ft_lstlast(head);
		cr_expect_eq(got, NULL,
			"\033[31mft_lstlast(NULL)\033[0m = \033[33m%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)got);
	}

	/* Case 2: single node */
	{
		t_list *a = make_node("a");
		t_list *got = ft_lstlast(a);
		cr_expect_eq(got, a,
			"\033[31mft_lstlast([a])\033[0m = \033[33m%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)got, (void *)a);
		free(a);
	}

	/* Case 3: multiple nodes */
	{
		t_list *a = make_node("a");
		t_list *b = make_node("b");
		t_list *c = make_node("c");
		a->next = b;
		b->next = c;

		t_list *got = ft_lstlast(a);
		cr_expect_eq(got, c,
			"\033[31mft_lstlast([a->b->c])\033[0m = \033[33m%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)got, (void *)c);

		free(a); free(b); free(c);
	}
}
