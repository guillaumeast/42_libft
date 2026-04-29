#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static bool	grow_and_insert(t_vector *vector, size_t index, const void *item);

// Warning: item must NOT be pointing inside vector->data
bool	vector_push(t_vector *vector, const void *item)
{
	void	*dst;

	if (vector->len == vector->cap)
		if (!vector_grow(vector))
			return (false);
	dst = vector->data + (vector->len * vector->item_size);
	ft_memcpy(dst, item, vector->item_size);
	vector->len++;
	return (true);
}

// Note: dst can be NULL
bool	vector_pop(t_vector *vector, void *dst)
{
	if (vector->len == 0)
		return (false);
	if (dst)
		ft_memcpy(
			dst,
			vector->data + ((vector->len - 1) * vector->item_size),
			vector->item_size);
	vector->len--;
	return (true);
}

// Warning: item must NOT be pointing inside vector->data
bool	vector_insert(t_vector *vector, size_t index, const void *item)
{
	if (index == vector->len)
		return (vector_push(vector, item));
	else if (index > vector->len)
		return (false);
	else if (vector->len == vector->cap)
		return (grow_and_insert(vector, index, item));
	ft_memmove(
		vector->data + ((index + 1) * vector->item_size),
		vector->data + (index * vector->item_size),
		(vector->len - index) * vector->item_size);
	ft_memcpy(
		vector->data + (index * vector->item_size),
		item,
		vector->item_size);
	vector->len++;
	return (true);
}

static bool	grow_and_insert(t_vector *vector, size_t index, const void *item)
{
	size_t	new_cap;
	void	*new_data;

	if (vector->cap > SIZE_T_MAX / 2)
		return (false);
	new_cap = vector->cap * 2;
	if (new_cap == 0)
		new_cap = VECTOR_INIT_CAP;
	if (new_cap > SIZE_T_MAX / vector->item_size)
		return (false);
	new_data = malloc(new_cap * vector->item_size);
	if (!new_data)
		return (false);
	vector->cap = new_cap;
	ft_memcpy(new_data, vector->data, index * vector->item_size);
	ft_memcpy(new_data + (index * vector->item_size), item, vector->item_size);
	ft_memcpy(
		new_data + ((index + 1) * vector->item_size),
		vector->data + (index * vector->item_size),
		(vector->len - index) * vector->item_size);
	free(vector->data);
	vector->data = new_data;
	vector->len++;
	return (true);
}

// Note: dst can be NULL
bool	vector_remove(t_vector *vector, size_t index, void *dst)
{
	if (index >= vector->len)
		return (false);
	if (index == vector->len - 1)
		return (vector_pop(vector, dst));
	if (dst)
		ft_memcpy(
			dst,
			vector->data + (index * vector->item_size),
			vector->item_size);
	ft_memmove(
		vector->data + (index * vector->item_size),
		vector->data + ((index + 1) * vector->item_size),
		(vector->len - index - 1) * vector->item_size);
	vector->len--;
	return (true);
}
