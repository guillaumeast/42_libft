#include <criterion/criterion.h>
#include "libft.h"
#include <string.h>

/* deleter: frees content and counts calls */
static int	del_called = 0;
static void	del_free_counter(void *content)
{
	free(content);
	del_called++;
}

static t_list	*make_node_dup(const char *s)
{
	t_list *n = (t_list *)malloc(sizeof(t_list));
	char   *dup;

	cr_assert_neq(n, NULL, "malloc failed");
	dup = strdup(s);
	cr_assert_neq(dup, NULL, "strdup failed");

	n->content = dup;
	n->next = NULL;
	return n;
}

Test(ft_lstclear, full_tests)
{
	/* Case 1: empty list */
	{
		del_called = 0;
		t_list *head = NULL;

		ft_lstclear(&head, del_free_counter);

		cr_expect_eq(head, NULL,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)head);
		cr_expect_eq(del_called, 0,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%d calls\033[0m (expected \033[33m0\033[0m)",
			del_called);
	}

	/* Case 2: three nodes -> cleared, del called 3 times */
	{
		del_called = 0;
		t_list *a = make_node_dup("a");
		t_list *b = make_node_dup("b");
		t_list *c = make_node_dup("c");
		t_list *head = a;
		a->next = b; b->next = c;

		ft_lstclear(&head, del_free_counter);

		cr_expect_eq(head, NULL,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)head);
		cr_expect_eq(del_called, 3,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%d calls\033[0m (expected \033[33m3\033[0m)",
			del_called);
	}

	/* Case 3: calling again on already NULL is safe and does nothing */
	{
		int before = del_called;
		t_list *head = NULL;

		ft_lstclear(&head, del_free_counter);

		cr_expect_eq(head, NULL,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)head);
		cr_expect_eq(del_called, before,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%d calls\033[0m (expected \033[33m%d\033[0m)",
			del_called, before);
	}

	/* Case 4: single node */
	{
		del_called = 0;
		t_list *head = make_node_dup("x");

		ft_lstclear(&head, del_free_counter);

		cr_expect_eq(head, NULL,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%p\033[0m (expected \033[33mNULL\033[0m)",
			(void *)head);
		cr_expect_eq(del_called, 1,
			"\033[31mft_lstclear(&head, del)\033[0m = \033[33m%d calls\033[0m (expected \033[33m1\033[0m)",
			del_called);
	}
}
