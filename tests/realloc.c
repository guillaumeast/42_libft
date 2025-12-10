#include "fut.h"
#include "libft.h"

#define MAX_LEN 1000000

static void	_test_realloc(size_t cap, size_t new_cap, char control_string[MAX_LEN])
{
	char	*buff;
	bool	realloc_res;

	if (cap == 0)
		buff = NULL;
	else
		buff = malloc(cap);
	memset(buff, 'A', cap);

	realloc_res = ft_realloc(&buff, cap, new_cap);
	assert_eq(RET, 0, realloc_res, true);
	if (new_cap == 0)
		assert_eq(RET, 0, buff, NULL);
	else
	{
		assert_neq(RET, 0, buff, NULL);
		assert_eq(RET, 0, memcmp(buff, control_string, cap), 0);
	}
	free(buff);
}

static void	_fail_realloc(size_t new_cap)
{
	char	*buff;
	bool	realloc_res;

	buff = NULL;
	realloc_res = ft_realloc(&buff, 0, new_cap);
	if (new_cap == 0)
		assert_eq(RET, 0, realloc_res, true);
	else
		assert_eq(RET, 0, realloc_res, false);
	assert_eq(RET, 0, buff, NULL);
	free(buff);
}

Test(test_realloc, 1)
{
	char	control_string[MAX_LEN];

	memset(control_string, 'A', MAX_LEN);

	_test_realloc(0, 0, control_string);
	_test_realloc(0, MAX_LEN, control_string);
	_test_realloc(MAX_LEN / 2, MAX_LEN, control_string);
	_test_realloc(MAX_LEN, MAX_LEN, control_string);
	_test_realloc(MAX_LEN, MAX_LEN / 2, control_string);
	_test_realloc(MAX_LEN, 0, control_string);

	memleaks(0, _test_realloc(0, 0, control_string));
	memleaks(0, _test_realloc(0, MAX_LEN, control_string));
	memleaks(0, _test_realloc(MAX_LEN / 2, MAX_LEN, control_string));
	memleaks(0, _test_realloc(MAX_LEN, MAX_LEN, control_string));
	memleaks(0, _test_realloc(MAX_LEN, MAX_LEN / 2, control_string));
	memleaks(0, _test_realloc(MAX_LEN, 0, control_string));

	memsafety(0, _fail_realloc(0));
	memsafety(0, _fail_realloc(MAX_LEN / 2));
	memsafety(0, _fail_realloc(MAX_LEN));
}
