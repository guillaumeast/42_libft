#include "libft.h"

int	ft_atoi(const char *str)
{
	return ((int)ft_atol(str));
}

char	*ft_itoa(int n)
{
	return (ft_ltoa((long) n));
}

char	*ft_utoa(unsigned int n)
{
	return (ft_ltoa((long) n));
}
