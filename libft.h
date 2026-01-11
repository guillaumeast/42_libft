/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:34:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/01/11 01:20:43 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

# define BUFFER_SIZE 128

/**
 * @struct s_buff
 * @brief Dynamic buffer structure for efficient string/data manipulation.
 *
 * @var s_buff::data Pointer to the allocated data.
 * @var s_buff::cap Current allocated capacity.
 * @var s_buff::len Current length of data in the buffer.
 */
typedef struct s_buff
{
	char	*data;
	size_t	cap;
	size_t	len;
}	t_buff;

/**
 * @struct s_node
 * @brief Doubly linked list node structure.
 *
 * @var s_node::content Pointer to the node's content.
 * @var s_node::prev Pointer to the previous node.
 * @var s_node::next Pointer to the next node.
 */
typedef struct s_node
{
	void			*content;
	struct s_node	*prev;
	struct s_node	*next;
}	t_node;

/**
 * @typedef t_list
 * @brief Type alias for a pointer to a list node (list head).
 */
typedef t_node	*t_list;

/*--------- BUFF ----------*/

/**
 * @brief Initializes a buffer with the specified initial capacity.
 *
 * @param b Pointer to the buffer structure to initialize.
 * @param initial_cap Initial capacity of the buffer.
 * @return true on success, false on memory allocation failure.
 *
 * @note Cannot fail when initial_cap == 0.
 */
bool	buff_init(t_buff *b, size_t initial_cap);

/**
 * @brief Calculates the required capacity to accommodate a target length.
 *
 * Uses exponential growth strategy (doubles capacity) to amortize
 * multiple growth operations to O(1) on average.
 *
 * @param current_cap Current capacity of the buffer.
 * @param target_len Target length to accommodate.
 * @return The new required capacity.
 */
size_t	buff_get_required_cap(size_t current_cap, size_t target_len);

/**
 * @brief Grows the buffer to accommodate the target length if necessary.
 *
 * No-op if current capacity is already sufficient.
 *
 * @param buff Pointer to an initialized buffer.
 * @param target_len The minimum length the buffer should accommodate.
 * @return true on success, false on memory allocation failure.
 *
 * @warning buff must be initialized before calling this function.
 */
bool	buff_grow(t_buff *buff, size_t target_len);

/**
 * @brief Shrinks buffer capacity to match its current length.
 *
 * @param buff Pointer to an initialized buffer.
 * @return true on success, false on memory allocation failure.
 *
 * @warning buff must be initialized before calling this function.
 */
bool	buff_adjust(t_buff *buff);

/**
 * @brief Frees the buffer's internal data.
 *
 * Sets buff->data to NULL after freeing.
 *
 * @param b Pointer to the buffer.
 *
 * @warning Does not free the t_buff struct, only its internal char* data.
 */
void	buff_free(t_buff *b);

/**
 * @brief Finds the index of a character in the buffer.
 *
 * @param buff Pointer to an initialized buffer.
 * @param c Character to find.
 * @return Index of the character, or -1 if not found.
 *
 * @warning buff must be initialized before calling this function.
 */
int		buff_get_index(t_buff *buff, char c);

/**
 * @brief Prepends a string to the beginning of the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @param b Pointer to an initialized buffer.
 * @param str String to prepend.
 * @param n Number of bytes to prepend, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 */
bool	buff_prepend(t_buff *b, const char *str, long n);

/**
 * @brief Inserts a string at a specific index in the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @param b Pointer to an initialized buffer.
 * @param index Position at which to insert the string.
 * @param str String to insert.
 * @param n Number of bytes to insert, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if index > b->len.
 * @warning UB if n > 0 and str is shorter than n bytes.
 */
bool	buff_insert(t_buff *b, size_t index, const char *str, long n);

/**
 * @brief Appends a string to the end of the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @param b Pointer to an initialized buffer.
 * @param str String to append.
 * @param n Number of bytes to append, or -1 to use strlen(str).
 * @return true on success, false on memory allocation failure.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 */
bool	buff_append(t_buff *b, const char *str, long n);

/**
 * @brief Duplicates up to n bytes of a buffer into a new buffer.
 *
 * @param src Source buffer to duplicate.
 * @param n Maximum number of bytes to copy.
 * @return Pointer to a newly allocated t_buff, or NULL on failure.
 *
 * @note Caller is responsible for freeing both the returned t_buff
 *       and its internal data (use buff_free then free).
 */
t_buff	*buff_dup_n(const t_buff *src, size_t n);

/**
 * @brief Removes a portion of the buffer starting at i_start.
 *
 * @param buff Pointer to an initialized buffer.
 * @param i_start Starting index for removal.
 * @param len Number of bytes to remove, or negative to remove until end.
 *
 * @note If len < 0, deletes all buffer content from i_start to end.
 *
 * @warning buff must be initialized before calling this function.
 */
void	buff_rm_part(t_buff *buff, size_t i_start, ssize_t len);

/**
 * @brief Appends formatted string to buffer using variadic arguments.
 *
 * Supports printf formats: `%c` `%s` `%d` `%i` `%u` `%x` `%X` `%p` `%%`.
 * Supports printf-like flags: `-` `0` `.` ` ` `#` `+`.
 *
 * @param buff Pointer to an initialized buffer.
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return true on success, false on failure.
 *
 * @warning buff must be initialized before calling this function.
 */
bool	buff_append_format(t_buff *buff, const char *fstring, ...)\
	__attribute__((format(printf, 2, 3)));

/**
 * @brief Appends formatted string to buffer using va_list.
 *
 * @param buff Pointer to an initialized buffer.
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return true on success, false on failure.
 *
 * @warning buff must be initialized before calling this function.
 */
bool	buff_append_vformat(t_buff *buff, const char *fstring, va_list args);

/**
 * @brief Reads from a file descriptor until a specific character is found.
 *
 * @param buff Pointer to an initialized buffer.
 * @param fd File descriptor to read from.
 * @param c Character to search for.
 * @return Index of c (>= 0), -1 if EOF reached before c, -2 on error.
 *
 * @warning buff must be initialized before calling this function.
 */
int		buff_read_until(t_buff *buff, int fd, char c);

/**
 * @brief Reads all available data from a file descriptor into buffer.
 *
 * @param buff Pointer to an initialized buffer.
 * @param fd File descriptor to read from.
 * @return true on success, false if read failed.
 *
 * @note On failure, buff->data is NOT automatically freed.
 *
 * @warning buff must be initialized before calling this function.
 */
bool	buff_read_all(t_buff *buff, int fd);

/*---------- CHR ----------*/

/**
 * @brief Checks if a character is alphanumeric.
 *
 * @param c Character to check.
 * @return Non-zero if alphanumeric, 0 otherwise.
 */
int		ft_isalnum(int c);

/**
 * @brief Checks if a character is alphabetic.
 *
 * @param c Character to check.
 * @return Non-zero if alphabetic, 0 otherwise.
 */
int		ft_isalpha(int c);

/**
 * @brief Checks if a character is a valid ASCII character (0-127).
 *
 * @param c Character to check.
 * @return Non-zero if ASCII, 0 otherwise.
 */
int		ft_isascii(int c);

/**
 * @brief Checks if a character is a digit ('0'-'9').
 *
 * @param c Character to check.
 * @return Non-zero if digit, 0 otherwise.
 */
int		ft_isdigit(int c);

/**
 * @brief Checks if a character is present in a character set.
 *
 * @param c Character to check.
 * @param charset Null-terminated string of characters to match against.
 * @return true if found in charset, false otherwise.
 */
bool	ft_isincharset(char c, const char *charset);

/**
 * @brief Checks if a character is printable (32-126).
 *
 * @param c Character to check.
 * @return Non-zero if printable, 0 otherwise.
 */
int		ft_isprint(int c);

/**
 * @brief Checks if a character is whitespace (9-13).
 *
 * @param c Character to check.
 * @return Non-zero if whitespace, 0 otherwise.
 */
int		ft_isspace(char c);

/**
 * @brief Converts an uppercase letter to lowercase.
 *
 * @param c Character to convert.
 * @return Lowercase equivalent if uppercase, otherwise unchanged.
 */
int		ft_tolower(int c);

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c Character to convert.
 * @return Uppercase equivalent if lowercase, otherwise unchanged.
 */
int		ft_toupper(int c);

/*--------- CONV ----------*/

/**
 * @brief Converts a string to an integer.
 *
 * @param str String to convert.
 * @return The converted integer value.
 */
int		ft_atoi(const char *str);

/**
 * @brief Converts a string to a long integer.
 *
 * @param str String to convert.
 * @return The converted long value.
 */
long	ft_atol(const char *str);

/**
 * @brief Converts an integer to a string.
 *
 * @param n Integer to convert.
 * @return Newly allocated string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_itoa(int n);

/**
 * @brief Converts an unsigned integer to a string.
 *
 * @param n Unsigned integer to convert.
 * @return Newly allocated string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_utoa(unsigned int n);

/**
 * @brief Converts a long integer to a string.
 *
 * @param n Long integer to convert.
 * @return Newly allocated string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_ltoa(long n);

/**
 * @brief Converts an unsigned long to a string in a given base.
 *
 * @param n Number to convert.
 * @param base String representing the base characters (must be >= 2 chars).
 * @return Newly allocated string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_ultoa_base(unsigned long n, const char *base);

/*---------- GNL ----------*/

/**
 * @brief Reads the next chunk from a file descriptor until separator is found.
 *
 * Returns the chunk even if EOF is reached before separator is found.
 * Returns NULL only when called after EOF has already been reached.
 *
 * @param fd File descriptor to read from.
 * @param separator Character to stop reading at (included in returned chunk).
 * @return Pointer to a newly allocated t_buff, or NULL on error/EOF.
 *
 * @note Caller is responsible for freeing the returned t_buff
 *       and its internal data (use buff_free then free).
 */
t_buff	*get_next_chunk(int fd, char separator);

/**
 * @brief Frees all internal stashes used by get_next_chunk.
 *
 * Call this to clean up when done reading from all file descriptors.
 */
void	get_next_chunk_free(void);

/*---------- LIST ----------*/

/**
 * @brief Creates a new list node.
 *
 * @param content Content for the new node (ownership transferred to node).
 * @param prev Pointer to the previous node (can be NULL).
 * @param next Pointer to the next node (can be NULL).
 * @return Pointer to the new node, or NULL on failure.
 *
 * @note Ownership of content is transferred to the node.
 */
t_node	*node_new(void *content, t_node *prev, t_node *next);

/**
 * @brief Frees a node and optionally its content.
 *
 * @param node Pointer to the node pointer (set to NULL after freeing).
 * @param del_content Function to delete the content (can be NULL to skip).
 */
void	node_free(t_node **node, void (*del_content)(void*));

/**
 * @brief Adds a new element at the end of the list.
 *
 * @param list Pointer to the list pointer.
 * @param new_content Content for the new node.
 * @return true on success, false on failure.
 *
 * @note Ownership of new_content is transferred to the list on success.
 */
bool	list_add_end(t_list *list, void *new_content);

/**
 * @brief Adds a new element at the start of the list.
 *
 * @param list Pointer to the list pointer.
 * @param new_content Content for the new node.
 * @return true on success, false on failure.
 *
 * @note Ownership of new_content is transferred to the list on success.
 */
bool	list_add_start(t_list *list, void *new_content);

/**
 * @brief Calculates the number of nodes in the list.
 *
 * @param list List to count.
 * @return Number of nodes in the list.
 */
size_t	list_get_size(t_list list);

/**
 * @brief Finds content in list matching a selection function.
 *
 * @param list List to search.
 * @param select_function Function returning true for desired content.
 * @return Matching content (not a copy), or NULL if not found.
 *
 * @note Returned pointer is NOT a copy; do not free it directly.
 */
void	*list_get_content(t_list list, bool (*select_function)(void*));

/**
 * @brief Gets content at a specific index in the list.
 *
 * @param list List to search.
 * @param index Zero-based index.
 * @return Content at index (not a copy), or NULL if index out of bounds.
 *
 * @note Returned pointer is NOT a copy; do not free it directly.
 */
void	*list_get_content_n(t_list list, size_t index);

/**
 * @brief Gets the content of the last node in the list.
 *
 * @param list List to search.
 * @return Content of last node (not a copy), or NULL if list is empty.
 *
 * @note Returned pointer is NOT a copy; do not free it directly.
 */
void	*list_get_content_last(t_list list);

/**
 * @brief Gets the node at a specific index in the list.
 *
 * @param list List to search.
 * @param index Zero-based index.
 * @return Node at index, or NULL if index out of bounds.
 */
t_node	*list_get_node_n(t_list list, size_t index);

/**
 * @brief Gets the last node in the list.
 *
 * @param list List to search.
 * @return Last node, or NULL if list is empty.
 */
t_node	*list_get_node_last(t_list list);

/**
 * @brief Applies a function to each element of the list.
 *
 * @param lst List to iterate over.
 * @param f Function to apply to each element's content.
 */
void	list_iter(t_list lst, void (*f)(void *));

/**
 * @brief Creates a new list by applying a function to each element.
 *
 * @param list Source list.
 * @param f Function to apply to each element (returns new content).
 * @param del Function to delete content on failure.
 * @return New list (caller owns it), or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned list.
 */
t_list	list_map(t_list list, void *(*f)(void *), void (*del)(void *));

/**
 * @brief Removes a specific node from the list.
 *
 * @param list Pointer to the list pointer.
 * @param node Node to remove.
 * @param del_content Function to delete the node's content (can be NULL).
 */
void	list_rm(t_list *list, t_node *node, void (*del_content)(void*));

/**
 * @brief Removes all nodes from the list.
 *
 * @param list Pointer to the list pointer (set to NULL after).
 * @param del_content Function to delete each node's content (can be NULL).
 */
void	list_rm_all(t_list *list, void (*del_content)(void*));

/*--------- MALLOC --------*/

/**
 * @brief Allocates and zeroes memory for an array.
 *
 * @param count Number of elements.
 * @param size Size of each element.
 * @return Pointer to allocated zeroed memory, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned memory.
 */
void	*ft_calloc(size_t count, size_t size);

/**
 * @brief Reallocates a buffer to a new capacity.
 *
 * @param buff Pointer to the buffer pointer.
 * @param cap Current capacity.
 * @param newcap New capacity (0 to free the buffer).
 * @return true on success, false on failure.
 *
 * @note If newcap is 0, *buff is freed and set to NULL.
 */
bool	ft_realloc(char **buff, size_t cap, size_t newcap);

/*--------- MATH --------*/

/**
 * @brief Calculates the exact integer square root.
 *
 * @param nb Number to find square root of.
 * @return Exact square root if nb is a perfect square, -1 otherwise.
 */
int		square_root_exact(int nb);

/**
 * @brief Calculates the nearest integer square root.
 *
 * @param nb Number to find square root of.
 * @return Nearest integer square root, -1 if nb <= 0.
 */
int		square_root_rounded(int nb);

/**
 * @brief Returns the minimum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The smaller value.
 */
int		ft_min(int a, int b);

/**
 * @brief Returns the maximum of two integers.
 *
 * @param a First integer.
 * @param b Second integer.
 * @return The larger value.
 */
int		ft_max(int a, int b);

/*---------- MEM ----------*/

/**
 * @brief Sets n bytes of memory to zero.
 *
 * @param s Pointer to memory area.
 * @param n Number of bytes to set.
 */
void	ft_bzero(void *s, size_t n);

/**
 * @brief Locates the first occurrence of a byte in memory.
 *
 * @param s Memory area to search.
 * @param c Byte to search for (converted to unsigned char).
 * @param n Number of bytes to search.
 * @return Pointer to the byte, or NULL if not found.
 */
void	*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares two memory areas byte by byte.
 *
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Number of bytes to compare.
 * @return Difference of first differing bytes, or 0 if equal.
 */
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Copies n bytes from src to dst.
 *
 * @param dst Destination memory area.
 * @param src Source memory area.
 * @param n Number of bytes to copy.
 * @return Pointer to dst.
 *
 * @warning Memory areas must not overlap. Use ft_memmove for overlapping.
 */
void	*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief Copies n bytes from src to dst, handling overlapping memory.
 *
 * @param dst Destination memory area.
 * @param src Source memory area.
 * @param len Number of bytes to copy.
 * @return Pointer to dst.
 */
void	*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief Fills memory with a constant byte.
 *
 * @param b Memory area to fill.
 * @param c Byte value to set (converted to unsigned char).
 * @param len Number of bytes to set.
 * @return Pointer to b.
 */
void	*ft_memset(void *b, int c, size_t len);

/*---------- PRINT ----------*/

/**
 * @brief Writes formatted output to a file descriptor using va_list.
 *
 * @param fd File descriptor to write to.
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_vdprintf(int fd, const char *fstring, va_list args);

/**
 * @brief Writes formatted output to a file descriptor.
 *
 * Supports printf formats: `%c` `%s` `%d` `%i` `%u` `%x` `%X` `%p` `%%`.
 * Supports printf-like flags: `-` `0` `.` ` ` `#` `+`.
 *
 * @param fd File descriptor to write to.
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_dprintf(int fd, const char *fstring, ...)\
	__attribute__((format(printf, 2, 3)));

/**
 * @brief Writes formatted output to stdout using va_list.
 *
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_vprintf(const char *fstring, va_list args);

/**
 * @brief Writes formatted output to stdout.
 *
 * Supports printf formats: `%c` `%s` `%d` `%i` `%u` `%x` `%X` `%p` `%%`.
 * Supports printf-like flags: `-` `0` `.` ` ` `#` `+`.
 *
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return Number of bytes written, or -1 on error.
 */
int		ft_printf(const char *fstring, ...)\
	__attribute__((format(printf, 1, 2)));

/*---------- PUT ----------*/

/**
 * @brief Writes a character to a file descriptor.
 *
 * @param c Character to write.
 * @param fd File descriptor to write to.
 */
void	ft_putchar_fd(char c, int fd);

/**
 * @brief Writes a string followed by newline to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void	ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes an integer to a file descriptor.
 *
 * @param n Integer to write.
 * @param fd File descriptor to write to.
 */
void	ft_putnbr_fd(int n, int fd);

/**
 * @brief Writes a string to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void	ft_putstr_fd(char *s, int fd);

/*---------- STR ----------*/

/**
 * @brief Splits a string into an array of strings using a delimiter.
 *
 * @param s String to split.
 * @param c Delimiter character.
 * @return NULL-terminated array of strings, or NULL on failure.
 *
 * @note Caller is responsible for freeing each string and the array.
 */
char	**ft_split(char const *s, char c);

/**
 * @brief Locates the first occurrence of a character in a string.
 *
 * @param s String to search.
 * @param c Character to find.
 * @return Pointer to the character, or NULL if not found.
 *
 * @note If c is '\\0', returns pointer to the terminating null.
 */
char	*ft_strchr(const char *s, int c);

/**
 * @brief Duplicates a string.
 *
 * @param s1 String to duplicate.
 * @return Newly allocated copy, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_strdup(const char *s1);

/**
 * @brief Applies a function to each character of a string with its index.
 *
 * @param s String to iterate (modified in place).
 * @param f Function taking index and character pointer.
 */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief Concatenates two strings into a new string.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return Newly allocated concatenated string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Appends src to dst with size limit.
 *
 * @param dst Destination buffer (must be null-terminated).
 * @param src Source string.
 * @param dstsize Total size of destination buffer.
 * @return Total length of string it tried to create.
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief Copies src to dst with size limit.
 *
 * @param dst Destination buffer.
 * @param src Source string.
 * @param dstsize Size of destination buffer.
 * @return Length of src.
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief Calculates the length of a string.
 *
 * @param s String to measure.
 * @return Length of the string (not including null terminator).
 */
size_t	ft_strlen(const char *s);

/**
 * @brief Creates a new string by applying a function to each character.
 *
 * @param s String to transform.
 * @param f Function taking index and character, returning new character.
 * @return Newly allocated transformed string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Compares at most n characters of two strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Maximum number of characters to compare.
 * @return Difference of first differing characters, or 0 if equal.
 */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief Locates a substring within a string, limited by length.
 *
 * @param haystack String to search in.
 * @param needle Substring to find.
 * @param len Maximum characters to search.
 * @return Pointer to start of substring, or NULL if not found.
 */
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

/**
 * @brief Locates the last occurrence of a character in a string.
 *
 * @param s String to search.
 * @param c Character to find.
 * @return Pointer to the character, or NULL if not found.
 *
 * @note If c is '\\0', returns pointer to the terminating null.
 */
char	*ft_strrchr(const char *s, int c);

/**
 * @brief Trims characters from the beginning and end of a string.
 *
 * @param s1 String to trim.
 * @param set Characters to trim.
 * @return Newly allocated trimmed string, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_strtrim(char const *s1, char const *set);

/**
 * @brief Extracts a substring from a string.
 *
 * @param s Source string.
 * @param start Starting index.
 * @param len Maximum length of substring.
 * @return Newly allocated substring, or NULL on failure.
 *
 * @note Caller is responsible for freeing the returned string.
 */
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
