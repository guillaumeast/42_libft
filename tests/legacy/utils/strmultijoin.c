#include "../test.h"

char	*ft_strmultijoin(char **strs, size_t size, char *sep)
{
	size_t	i;
	size_t	res_len;
	char	*res;

	i = 0;
	res_len = 0;
	while (i < size)
	{
		res_len += ft_strlen(strs[i]);
		if (i < size - 1)
			res_len += ft_strlen(sep);
		i++;
	}
	res = ft_calloc(res_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ft_strlcat(res, strs[i], res_len + 1);
		if (i < size - 1)
			ft_strlcat(res, sep, res_len + 1);
		i++;
	}
	return (res);
}
