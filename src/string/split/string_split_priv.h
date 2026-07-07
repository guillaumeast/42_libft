#ifndef STRING_SPLIT_PRIV_H
# define STRING_SPLIT_PRIV_H

# include "libft.h"

bool	string_add_to_vector(
			const t_string *src,
			size_t start,
			size_t len,
			t_vector *out);
bool	string_is_sep(
			const t_string *src,
			size_t i,
			const char *sep);

#endif
