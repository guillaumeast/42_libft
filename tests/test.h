#ifndef TEST_H
# define TEST_H

# include "libft.h"
# include <string.h>	// strcmp

// Utils
int		test_int(char *f_name, char *input, int expected_output, int output);
int		test_str(char *f_name, char *input, char *expected_output, char *output);
void	print_success(char *f_name, char *input, char *output);
void	print_failure(char *f_name, char *input, char *output, char *expected);
void	print_result(int score, int max_score);

// Unit tests (Part 1)
int		test_ft_isalpha(void);
int		test_ft_isdigit(void);
int		test_ft_isalnum(void);
int		test_ft_isascii(void);
int		test_ft_isprint(void);
int		test_ft_strlen(void);
int		test_ft_memset(void);
int		test_ft_bzero(void);
int		test_ft_memcpy(void);
int		test_ft_memmove(void);
int		test_ft_strlcpy(void);
int		test_ft_strlcat(void);
int		test_ft_toupper(void);
int		test_ft_tolower(void);
int		test_ft_strchr(void);
int		test_ft_strrchr(void);
int		test_ft_strncmp(void);
int		test_ft_memchr(void);
int		test_ft_memcmp(void);
int		test_ft_strnstr(void);
int		test_ft_atoi(void);
int		test_ft_calloc(void);
int		test_ft_strdup(void);

// Unit tests (Part 2)

#endif