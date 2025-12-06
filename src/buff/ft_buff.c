#include "libft.h"
#include <stdlib.h>

#define BUFF_SIZE 512
#define BUFF_GROWTH 2

// TODO: test all

bool	buff_init(t_buff *b)
{
	b->data = malloc(BUFF_SIZE);
	if (!b)
		return (false);
	b->cap = BUFF_SIZE;
	b->len = 0;
	return (true);
}

bool	buff_prepend(t_buff *b, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	if (b->len + strlen >= b->cap)
	{
		new_data = malloc(b->cap * BUFF_GROWTH);
		if (!new_data)
			return (false);
		b->cap = b->cap * BUFF_GROWTH;
		ft_memcpy(new_data + strlen, b->data, b->len);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + strlen, b->data, b->len);
	ft_memcpy(b->data, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_insert(t_buff *b, size_t index, const char *str, long n)
{
	size_t	strlen;
	char	*new_data;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	if (b->len + strlen >= b->cap)
	{
		new_data = malloc(b->cap * BUFF_GROWTH);
		if (!new_data)
			return (false);
		b->cap = b->cap * BUFF_GROWTH;
		ft_memcpy(new_data, b->data, index);
		ft_memcpy(new_data + index + strlen, b->data + index, b->len - index);
		free(b->data);
		b->data = new_data;
	}
	else
		ft_memmove(b->data + index + strlen, b->data + index, b->len - index);
	ft_memcpy(b->data + index, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

bool	buff_append(t_buff *b, const char *str, long n)
{
	size_t	strlen;

	if (n < 0)
		strlen = ft_strlen(str);
	else
		strlen = (size_t)n;
	if (b->len + strlen >= b->cap)
	{
		if (!ft_realloc(&b->data, b->cap, b->cap * BUFF_GROWTH))
			return (false);
	}
	ft_memcpy(b->data, str, strlen);
	b->len = b->len + strlen;
	return (true);
}

void	buff_free(t_buff *b)
{
	if (b->data)
		free(b->data);
	b->data = NULL;
}
