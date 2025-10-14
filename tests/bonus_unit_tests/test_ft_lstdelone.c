#include <criterion/criterion.h>
#include "libft.h"

/* simple deleter to check calls */
static int	del_called = 0;
static void	del_counter(void *content)
{
	(void)content;
	del_called++;
}

static t_list	*make_node(void *content)
{
	t_list *n = (t_list *)malloc(sizeof(t_list));
	cr_assert_neq(n, NULL, "malloc failed");
	n->content = content;
	n->next = NULL;
	return n;
}

Test(ft_lstdelone, full_tests)
{
	/* Case 1: delete single node, del called once */
	{
		del_called = 0;
		t_list *n = make_node("a");

		ft_lstdelone(n, del_counter);

		cr_expect_eq(del_called, 1,
			"\033[31mft_lstdelone(node, del)\033[0m = \033[33m%d calls\033[0m (expected \033[33m1\033[0m)",
			del_called);
	}

	/* Case 2: lst == NULL -> nothing called */
	{
		del_called = 0;
		ft_lstdelone(NULL, del_counter);

		cr_expect_eq(del_called, 0,
			"\033[31mft_lstdelone(NULL, del)\033[0m = \033[33m%d calls\033[0m (expected \033[33m0\033[0m)",
			del_called);
	}

	/* Case 3: del == NULL -> should not crash */
	{
		t_list *n = make_node("b");
		ft_lstdelone(n, NULL);
		/* cannot verify much, only check it didn't crash */
		cr_expect(1, "\033[31mft_lstdelone(node, NULL)\033[0m did not crash (expected safe behavior)");
	}
}
