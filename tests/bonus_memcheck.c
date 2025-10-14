#include "libft.h"

// TODO: use all functions which use malloc
int	main(void)
{
	char	*s1 = ft_strdup("Hello");
	char	*s2 = ft_strjoin(s1, " world!");

	printf("%s\n", s2);

	free(s1);
	free(s2);
	return (0);
}
