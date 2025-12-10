#include <stdlib.h>
#include <stdbool.h>

bool	ft_realloc(char **buff, size_t cap, size_t newcap)
{
	char	*new_buff;
	size_t	i;

	if (newcap == 0)
	{
		free(*buff);
		*buff = NULL;
		return (true);
	}
	new_buff = malloc(newcap);
	if (!new_buff)
		return (false);
	i = 0;
	while (i < cap)
	{
		new_buff[i] = (*buff)[i];
		i++;
	}
	free(*buff);
	*buff = new_buff;
	return (true);
}
