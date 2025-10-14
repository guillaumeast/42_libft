#include <criterion/criterion.h>
#include "libft.h"
#include <string.h>

/* iterator that uppercases the first character of each string */
static void	iter_upper_first(void *content)
{
	char *s = (char *)content;
	if (s && s[0] >= 'a' && s[0] <= 'z')
		s[0] -= 32;
}

/* iterator that appends '*' at the end of each string (if space available) */
static void	iter_star(void *content)
{
	char *s = (char *)content;
	size_t len = strlen(s);
	if (len < 63) {
		s[len] = '*';
		s[len + 1] = '\0';
	}
}

static t_list	*make_node_dup(const char *s)
{
	t_list *n = (t_list *)malloc(sizeof(t_list));
	char   *dup = strdup(s);
	cr_assert_neq(dup, NULL, "strdup failed");
	n->content = dup;
	n->next = NULL;
	return n;
}

static void	free_list(t_list *lst)
{
	while (lst) {
		free(lst->content);
		t_list *tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

Test(ft_lstiter, full_tests)
{
	/* Case 1: apply upper_first on multiple nodes */
	{
		t_list *a = make_node_dup("alpha");
		t_list *b = make_node_dup("bravo");
		t_list *c = make_node_dup("charlie");
		a->next = b; b->next = c;

		ft_lstiter(a, iter_upper_first);

		cr_expect_str_eq(a->content, "Alpha",
			"\033[31mft_lstiter(list, upper_first)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"Alpha\"\033[0m)",
			(char *)a->content);
		cr_expect_str_eq(b->content, "Bravo",
			"\033[31mft_lstiter(list, upper_first)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"Bravo\"\033[0m)",
			(char *)b->content);
		cr_expect_str_eq(c->content, "Charlie",
			"\033[31mft_lstiter(list, upper_first)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"Charlie\"\033[0m)",
			(char *)c->content);

		free_list(a);
	}

	/* Case 2: append '*' */
	{
		t_list *a = make_node_dup("one");
		t_list *b = make_node_dup("two");
		a->next = b;

		ft_lstiter(a, iter_star);

		cr_expect_str_eq(a->content, "one*",
			"\033[31mft_lstiter(list, star)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"one*\"\033[0m)",
			(char *)a->content);
		cr_expect_str_eq(b->content, "two*",
			"\033[31mft_lstiter(list, star)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"two*\"\033[0m)",
			(char *)b->content);

		free_list(a);
	}

	/* Case 3: NULL list should not crash */
	{
		ft_lstiter(NULL, iter_upper_first);
		cr_expect(1, "\033[31mft_lstiter(NULL, f)\033[0m did not crash (expected safe behavior)");
	}
}
