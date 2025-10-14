#include "libft.h"
#include <string.h>

/* helper: simple iterator for ft_lstiter (prints each node's content) */
static void	iter_print(void *content)
{
	if (content)
		puts((const char *)content);
}

/* helper: free the result of ft_split */
static void	free_split(char **arr)
{
	if (!arr)
		return;
	for (size_t i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

/* helper: sample mapper for ft_strmapi */
static char	mapper(unsigned int i, char c)
{
	(void)i;
	return (char)(c + 1);
}

int	main(void)
{
	/* --- ft_calloc -------------------------------------------------- */
	void *p1 = ft_calloc(10, sizeof(int));
	void *p2 = ft_calloc(0, 4);
	void *p3 = ft_calloc(4, 0);
	free(p1);
	free(p2);
	free(p3);

	/* --- ft_strdup -------------------------------------------------- */
	char *dup1 = ft_strdup("Hello");
	char *dup2 = ft_strdup("");
	free(dup1);
	free(dup2);

	/* --- ft_substr -------------------------------------------------- */
	char *sub1 = ft_substr("abcdef", 2, 3);
	char *sub2 = ft_substr("hi", 42, 5);
	free(sub1);
	free(sub2);

	/* --- ft_strjoin ------------------------------------------------- */
	char *join1 = ft_strjoin("Hello", " world");
	char *join2 = ft_strjoin("", "");
	free(join1);
	free(join2);

	/* --- ft_strtrim ------------------------------------------------- */
	char *trim1 = ft_strtrim("  hello  ", " ");
	char *trim2 = ft_strtrim("xx42xx", "x");
	char *trim3 = ft_strtrim("", " ");
	free(trim1);
	free(trim2);
	free(trim3);

	/* --- ft_split --------------------------------------------------- */
	char **sp1 = ft_split("one,two,three", ',');
	char **sp2 = ft_split("a  b   c", ' ');
	char **sp3 = ft_split("", ',');
	free_split(sp1);
	free_split(sp2);
	free_split(sp3);

	/* --- ft_itoa ---------------------------------------------------- */
	char *itoa1 = ft_itoa(0);
	char *itoa2 = ft_itoa(2147483647);
	char *itoa3 = ft_itoa(-2147483648);
	free(itoa1);
	free(itoa2);
	free(itoa3);

	/* --- ft_strmapi ------------------------------------------------- */
	char *mapi1 = ft_strmapi("abcd", mapper); /* bcde */
	char *mapi2 = ft_strmapi("", mapper);     /* ""   */
	free(mapi1);
	free(mapi2);

	/*------------------------------------------------------------------*/
	/*								BONUS								*/
	/*------------------------------------------------------------------*/

	/* --- ft_lstnew -------------------------------------------------- */
	t_list *n1 = ft_lstnew(ft_strdup("node1"));
	t_list *n2 = ft_lstnew(ft_strdup("node2"));
	t_list *n3 = ft_lstnew(ft_strdup("node3"));

	/* --- ft_lstadd_front -------------------------------------------- */
	ft_lstadd_front(&n1, n2);    /* n2 -> n1 */

	/* --- ft_lstadd_back --------------------------------------------- */
	ft_lstadd_back(&n1, n3);     /* n2 -> n1 -> n3 */

	/* --- ft_lstsize ------------------------------------------------- */
	int size = ft_lstsize(n1);
	(void)size; /* silence unused warning */

	/* --- ft_lstlast ------------------------------------------------- */
	t_list *last = ft_lstlast(n1);
	(void)last;

	/* --- ft_lstsize ------------------------------------------------- */
	ft_lstiter(n1, iter_print);

	/* --- ft_lstclear ------------------------------------------------ */
	t_list *mapped = ft_lstmap(n1, (void *(*)(void *))ft_strdup, free);
	ft_lstclear(&mapped, free);

	/* clean all remaining nodes */
	ft_lstclear(&n1, free);

	return 0;
}
