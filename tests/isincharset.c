#include "fut.h"
#include "libft.h"

Test(test_isincharset, 0)
{
	static const char	charset[] = "%csdiuxXp";
	size_t				charset_size;
	size_t				i;

	charset_size = sizeof charset / sizeof *charset - 1;
	i = 0;
	while (i < charset_size)
	{
		assert_eq(RET, 1, ft_isincharset(charset[i], charset), true);
		i++;
	}
	assert_eq(RET, 1, ft_isincharset('a', charset), false);
	assert_eq(RET, 1, ft_isincharset('P', charset), false);
	assert_eq(RET, 1, ft_isincharset('\0', charset), false);
}
