#include "libft.h"
#include <stdlib.h>
#include <limits.h>

static bool	grow_and_merge(t_vector *dst, t_vector *src, size_t index);
static bool	compute_new_cap(size_t dst_len, size_t src_len, size_t *new_cap);

bool	vector_merge(t_vector *dst, t_vector *src, size_t index)
{
	size_t	target_len;

	if (dst == src)
		return (false);
	if (index > dst->len)
		return (false);
	if (dst->item_size != src->item_size)
		return (false);
	if (dst->len > SIZE_T_MAX - src->len)
		return (false);
	target_len = dst->len + src->len;
	if (dst->cap < target_len)
		return (grow_and_merge(dst, src, index));
	ft_memmove(
		dst->data + ((index + src->len) * dst->item_size),
		dst->data + (index * dst->item_size),
		(dst->len - index) * dst->item_size);
	ft_memcpy(
		dst->data + (index * dst->item_size),
		src->data,
		src->len * src->item_size);
	dst->len = target_len;
	return (true);
}

static bool	grow_and_merge(t_vector *dst, t_vector *src, size_t index)
{
	size_t	new_cap;
	void	*new_data;

	new_cap = dst->cap;
	if (new_cap == 0)
		new_cap = VECTOR_INIT_CAP;
	if (!compute_new_cap(dst->len, src->len, &new_cap)
		|| new_cap > SIZE_T_MAX / dst->item_size)
		return (false);
	new_data = malloc(new_cap * dst->item_size);
	if (!new_data)
		return (false);
	ft_memcpy(new_data, dst->data, index * dst->item_size);
	ft_memcpy(
		new_data + ((index + src->len) * dst->item_size),
		dst->data + (index * dst->item_size),
		(dst->len - index) * dst->item_size);
	ft_memcpy(
		new_data + (index * dst->item_size), src->data,
		src->len * dst->item_size);
	free(dst->data);
	dst->data = new_data;
	dst->cap = new_cap;
	dst->len += src->len;
	return (true);
}

static bool	compute_new_cap(size_t dst_len, size_t src_len, size_t *new_cap)
{
	size_t	target_len;
	size_t	tmp_new_cap;

	if (dst_len > SIZE_T_MAX - src_len)
		return (false);
	target_len = dst_len + src_len;
	if (!new_cap || *new_cap > SIZE_T_MAX / 2)
		return (false);
	tmp_new_cap = *new_cap;
	while (tmp_new_cap < target_len)
	{
		if (tmp_new_cap > SIZE_T_MAX / 2)
			return (false);
		tmp_new_cap *= 2;
	}
	*new_cap = tmp_new_cap;
	return (true);
}
