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

Test(ft_lstadd_back, full_tests)
{
	/* Case 1: add to empty list */
	{
		t_list *head = NULL;
		t_list *a = make_node("a");

		ft_lstadd_back(&head, a);

		cr_expect_eq(head, a,
			"\033[31mft_lstadd_back(&head, a)\033[0m = \033[33mhead=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)head, (void *)a);
		cr_expect_eq(a->next, NULL,
			"\033[31mft_lstadd_back(&head, a)\033[0m = \033[33ma->next=%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)a->next);

		free(a);
	}

	/* Case 2: add to non-empty list */
	{
		t_list *a = make_node("a");
		t_list *b = make_node("b");
		t_list *c = make_node("c");
		a->next = b;

		ft_lstadd_back(&a, c);

		cr_expect_eq(b->next, c,
			"\033[31mft_lstadd_back(&a, c)\033[0m = \033[33mb->next=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)b->next, (void *)c);
		cr_expect_eq(c->next, NULL,
			"\033[31mft_lstadd_back(&a, c)\033[0m = \033[33mc->next=%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)c->next);

		free(a); free(b); free(c);
	}

	/* Case 3: new == NULL -> unchanged */
	{
		t_list *x = make_node("x");
		ft_lstadd_back(&x, NULL);

		cr_expect_eq(x->next, NULL,
			"\033[31mft_lstadd_back(&x, NULL)\033[0m = \033[33mx->next=%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)x->next);

		free(x);
	}
}
