#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	while ((line = gnl(fd)))
	{
		printf("%s", line);
		free(line);
	}
    close(fd);
	return (0);
}
