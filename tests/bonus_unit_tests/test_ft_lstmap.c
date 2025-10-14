#include <criterion/criterion.h>
#include "libft.h"
#include <string.h>

/* mapping functions */
static void	*map_dup_upper(void *content)
{
	char *s = (char *)content;
	char *dup = strdup(s);
	if (!dup)
		return NULL;
	for (size_t i = 0; dup[i]; i++)
		if (dup[i] >= 'a' && dup[i] <= 'z')
			dup[i] -= 32;
	return dup;
}

static void	*map_star(void *content)
{
	char *s = (char *)content;
	size_t len = strlen(s);
	char *dup = malloc(len + 2);
	if (!dup)
		return NULL;
	strcpy(dup, s);
	dup[len] = '*';
	dup[len + 1] = '\0';
	return dup;
}

/* deleter */
static int	del_called = 0;
static void	del_counter(void *content)
{
	free(content);
	del_called++;
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

Test(ft_lstmap, full_tests)
{
	/* Case 1: normal mapping */
	{
		t_list *a = make_node_dup("alpha");
		t_list *b = make_node_dup("bravo");
		t_list *c = make_node_dup("charlie");
		a->next = b; b->next = c;

		t_list *new = ft_lstmap(a, map_dup_upper, del_counter);

		cr_expect_neq(new, NULL,
			"\033[31mft_lstmap(list, upper, del)\033[0m = \033[33mNULL\033[0m (expected \033[33mnew list\033[0m)");
		if (new) {
			cr_expect_str_eq(new->content, "ALPHA",
				"\033[31mft_lstmap(list, upper, del)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"ALPHA\"\033[0m)",
				(char *)new->content);
			cr_expect_str_eq(new->next->content, "BRAVO",
				"\033[31mft_lstmap(list, upper, del)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"BRAVO\"\033[0m)",
				(char *)new->next->content);
			cr_expect_str_eq(new->next->next->content, "CHARLIE",
				"\033[31mft_lstmap(list, upper, del)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"CHARLIE\"\033[0m)",
				(char *)new->next->next->content);
			cr_expect_eq(new->next->next->next, NULL,
				"\033[31mft_lstmap(list, upper, del)\033[0m = \033[33mnon-NULL terminator\033[0m (expected \033[33mNULL\033[0m)");
			free_list(new);
		}
		free_list(a);
	}

	/* Case 2: apply map_star */
	{
		t_list *a = make_node_dup("foo");
		t_list *b = make_node_dup("bar");
		a->next = b;

		t_list *new = ft_lstmap(a, map_star, del_counter);

		cr_expect_str_eq(new->content, "foo*",
			"\033[31mft_lstmap(list, star, del)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"foo*\"\033[0m)",
			(char *)new->content);
		cr_expect_str_eq(new->next->content, "bar*",
			"\033[31mft_lstmap(list, star, del)\033[0m = \033[33m\"%s\"\033[0m (expected \033[33m\"bar*\"\033[0m)",
			(char *)new->next->content);

		free_list(new);
		free_list(a);
	}

	/* Case 3: NULL list -> returns NULL */
	{
		t_list *res = ft_lstmap(NULL, map_star, del_counter);
		cr_expect_eq(res, NULL,
			"\033[31mft_lstmap(NULL, f, del)\033[0m = \033[33mnon-NULL\033[0m (expected \033[33mNULL\033[0m)");
	}

	/* Case 4: NULL f -> returns NULL safely */
	{
		t_list *x = make_node_dup("x");
		t_list *res = ft_lstmap(x, NULL, del_counter);
		cr_expect_eq(res, NULL,
			"\033[31mft_lstmap(list, NULL, del)\033[0m = \033[33mnon-NULL\033[0m (expected \033[33mNULL\033[0m)");
		free_list(x);
	}
}
