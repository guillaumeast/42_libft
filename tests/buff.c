#include "fut.h"
#include "libft.h"
#include "../src/buff/buff_internal.h"
#include <stdio.h>

#define MAX_LEN 1000000
static size_t	tested_cap[] = {0, 1, 1024, MAX_LEN};
static size_t	tested_len[] = {0, 1, 1024, MAX_LEN};

/*-------------------- init --------------------*/

Test(test_buff_init, 1)
{
	t_buff	buff;

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		buff_init(&buff, tested_cap[i]);
		assert(0, buff.cap == tested_cap[i]);
		assert_eq(RET, 0, buff.len, 0);
		if (tested_cap[i] == 0)
			assert_eq(RET, 0, buff.data, NULL);
		else
			assert_neq(RET, 0, buff.data, NULL);
		buff_free(&buff);
	}
}

/*-------------------- get_required_cap --------------------*/

Test(test_buff_get_required_cap, 1)
{
	t_buff	buff;
	size_t	result;

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			buff_init(&buff, tested_cap[i]);
			result = buff_get_required_cap(buff.cap, tested_len[j]);
			if (buff.cap > tested_len[j] || tested_len[j] == 0)
				assert(0, result == buff.cap);
			else
				assert(0, result > tested_len[j]);
			buff_free(&buff);
		}
	}
}

/*-------------------- prepend --------------------*/

static void	test_prepend_n(const char *s1, const char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	total_len = len * 2;
	memcpy(expected, s2, len);
	memcpy(expected + len, s1, len);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_prepend(&buff, s2, (long)len);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	buff_free(&buff);
}

static void	test_prepend_auto(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	if (len == 0)
		return ;
	s2[len] = '\0';

	total_len = len * 2;
	memcpy(expected, s2, len);
	memcpy(expected + len, s1, len);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_prepend(&buff, s2, -1);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	s2[len] = 'B';
	buff_free(&buff);
}

static void	test_prepend_mem(const char *s1, const char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];

	memcpy(expected, s2, len);
	memcpy(expected + len, s1, len);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_prepend(&buff, s2, (long)len);
	buff_free(&buff);
}

Test(test_buff_prepend, 1)
{
	char	s1[MAX_LEN];
	char	s2[MAX_LEN];

	memset(s1, 'A', MAX_LEN);
	memset(s2, 'B', MAX_LEN);

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			test_prepend_n(s1, s2, tested_cap[i], tested_len[j]);
			test_prepend_auto(s1, s2, tested_cap[i], tested_len[j]);
			memleaks(0, test_prepend_mem(s1, s2, tested_cap[i], tested_len[j]));
			memsafety(0, test_prepend_mem(s1, s2, tested_cap[i], tested_len[j]));
		}
	}
}

/*-------------------- insert --------------------*/

static void	test_insert_n(const char *s1, const char *s2, size_t cap, size_t len, size_t i)
{
	t_buff		buff;
	char		expected[MAX_LEN * 2];
	size_t		total_len;

	total_len = len * 2;
	memcpy(expected, s1, i);
	memcpy(expected + i, s2, len);
	memcpy(expected + i + len, s1, len - i);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_insert(&buff, i, s2, (long)len);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);

	buff_free(&buff);
}

static void	test_insert_auto(const char *s1, char *s2, size_t cap, size_t len, size_t i)
{
	t_buff		buff;
	char		expected[MAX_LEN * 2];
	size_t		total_len;

	if (len == 0)
		return ;
	s2[len] = '\0';

	total_len = len * 2;
	memcpy(expected, s1, i);
	memcpy(expected + i, s2, len);
	memcpy(expected + i + len, s1, len - i);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_insert(&buff, i, s2, -1);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	s2[len] = 'B';
	buff_free(&buff);
}

static void	test_insert_mem(const char *s1, const char *s2, size_t cap, size_t len, size_t i)
{
	t_buff		buff;
	char		expected[MAX_LEN * 2];

	memcpy(expected, s1, i);
	memcpy(expected + i, s2, len);
	memcpy(expected + i + len, s1, len - i);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_insert(&buff, i, s2, (long)len);
	buff_free(&buff);
}

Test(test_buff_insert, 1)
{
	char	s1[MAX_LEN + 1];
	char	s2[MAX_LEN + 1];

	memset(s1, 'A', MAX_LEN);
	memset(s2, 'B', MAX_LEN);
	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			test_insert_n(s1, s2, tested_cap[i], tested_len[j], 0);
			test_insert_auto(s1, s2, tested_cap[i], tested_len[j], 0);
			memleaks(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], 0));
			memsafety(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], 0));
			if (tested_len[j] == 0)
				continue ;
			test_insert_n(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2);
			test_insert_auto(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2);
			memleaks(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2));
			memsafety(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j] / 2));
			test_insert_n(s1, s2, tested_cap[i], tested_len[j], tested_len[j]);
			test_insert_auto(s1, s2, tested_cap[i], tested_len[j], tested_len[j]);
			memleaks(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j]));
			memsafety(0, test_insert_mem(s1, s2, tested_cap[i], tested_len[j], tested_len[j]));
		}
	}
}

/*-------------------- append --------------------*/

static void test_append_n(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	total_len = len * 2;
	memcpy(expected, s1, len);
	memcpy(expected + len, s2, len);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_append(&buff, s2, (long)len);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	buff_free(&buff);
}

static void test_append_auto(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];
	size_t	total_len;

	if (len == 0)
		return ;
	s2[len] = '\0';

	total_len = len * 2;
	memcpy(expected, s1, len);
	memcpy(expected + len, s2, len);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_append(&buff, s2, (long)-1);

	if (total_len > 0)
		assert(0, buff.cap > total_len);
	else
		assert_eq(RET, 0, buff.cap, cap);
	assert_eq(RET, 0, buff.len, total_len);
	assert(0, memcmp(buff.data, expected, total_len) == 0);
	
	s2[len] = 'B';
	buff_free(&buff);
}

static void test_append_mem(const char *s1, char *s2, size_t cap, size_t len)
{
	t_buff	buff;
	char	expected[MAX_LEN * 2];

	memcpy(expected, s1, len);
	memcpy(expected + len, s2, len);

	buff_init(&buff, cap);
	buff_append(&buff, s1, (long)len);
	buff_append(&buff, s2, (long)len);
	buff_free(&buff);
}

Test(test_buff_append, 1)
{
	char	s1[MAX_LEN];
	char	s2[MAX_LEN];

	memset(s1, 'A', MAX_LEN);
	memset(s2, 'B', MAX_LEN);

	for (size_t i = 0; i < sizeof tested_cap / sizeof *tested_cap; i++)
	{
		for (size_t j = 0; j < sizeof tested_len / sizeof *tested_len; j++)
		{
			test_append_n(s1, s2, tested_cap[i], tested_len[j]);
			test_append_auto(s1, s2, tested_cap[i], tested_len[j]);
			memleaks(0, test_append_mem(s1, s2, tested_cap[i], tested_len[j]));
			memsafety(0, test_append_mem(s1, s2, tested_cap[i], tested_len[j]));
		}
	}
}
