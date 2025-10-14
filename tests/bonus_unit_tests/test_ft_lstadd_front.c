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

Test(ft_lstadd_front, full_tests)
{
	/* Case 1: add to non-empty list */
	{
		t_list	*head = NULL;
		t_list	*b = make_node("b");
		t_list	*c = make_node("c");
		t_list	*a = make_node("a");

		head = b;
		b->next = c;

		ft_lstadd_front(&head, a);

		/* head must be 'a' */
		cr_expect_eq(head, a,
			"\033[31mft_lstadd_front(&head, a)\033[0m = \033[33mhead=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)head, (void *)a);

		/* a->next must be old head ('b') */
		cr_expect_eq(a->next, b,
			"\033[31mft_lstadd_front(&head, a)\033[0m = \033[33ma->next=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)a->next, (void *)b);

		/* tail still 'c' and next NULL */
		cr_expect_eq(b->next, c,
			"\033[31mft_lstadd_front(&head, a)\033[0m = \033[33mb->next=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)b->next, (void *)c);
		cr_expect_eq(c->next, NULL,
			"\033[31mft_lstadd_front(&head, a)\033[0m = \033[33mc->next=%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)c->next);

		free(a); free(b); free(c);
	}

	/* Case 2: add to empty list */
	{
		t_list	*head = NULL;
		t_list	*x = make_node("x");

		ft_lstadd_front(&head, x);

		cr_expect_eq(head, x,
			"\033[31mft_lstadd_front(&head, x)\033[0m = \033[33mhead=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)head, (void *)x);
		cr_expect_eq(x->next, NULL,
			"\033[31mft_lstadd_front(&head, x)\033[0m = \033[33mx->next=%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)x->next);

		free(x);
	}

	/* Case 3: new == NULL -> list unchanged */
	{
		t_list	*head = NULL;
		t_list	*y = make_node("y");
		head = y;

		ft_lstadd_front(&head, NULL);

		cr_expect_eq(head, y,
			"\033[31mft_lstadd_front(&head, NULL)\033[0m = \033[33mhead=%p\033[0m (expected \033[33m%p\033[0m)",
			(void *)head, (void *)y);
		cr_expect_eq(y->next, NULL,
			"\033[31mft_lstadd_front(&head, NULL)\033[0m = \033[33my->next=%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)y->next);

		free(y);
	}
}
