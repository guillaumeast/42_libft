/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gastesan <gastesan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:34:40 by gastesan          #+#    #+#             */
/*   Updated: 2026/07/06 19:48:27 by gastesan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/types.h>

# define BUFFER_SIZE		128
# define VECTOR_INIT_CAP	16

/* ************************************************************************* */
/*                                   TYPES                                   */
/* ************************************************************************* */

/**
 * @brief Temporary pointer view used to reinterpret the same address with or
 *        without const qualification.
 *
 * This helper does not duplicate data; it only exposes the same pointer as
 * either const char * or char * when a borrowed string address must be
 * returned through a non-const API.
 */
typedef union u_const_cast
{
	const char	*str;
	char		*res;
}	t_const_cast;

/* --------------------------------- T_BUFF -------------------------------- */

/**
 * @struct s_buff
 * @brief Dynamic buffer structure for efficient string/data manipulation.
 *
 * @var s_buff::data Pointer to the allocated data (owned by the buffer).
 * @var s_buff::cap Current allocated capacity.
 * @var s_buff::len Current length of data in the buffer.
 */
typedef struct s_buff
{
	/** @brief Pointer to the allocated data (owned). */
	char	*data;
	/** @brief Current allocated capacity (in bytes). */
	size_t	cap;
	/** @brief Current length of data in the buffer (in bytes). */
	size_t	len;
}	t_buff;

/* -------------------------------- T_STRING ------------------------------- */

/**
 * @struct s_string
 * @brief Dynamic string structure with NUL-terminated storage.
 *
 * @warning When cap == 0, data is NULL and must not be used as a C string.
 *          Call a function that allocates storage before reading data.
 *
 * @var s_string::data Pointer to the allocated data (owned, NUL-terminated
 *                     when cap > 0).
 * @var s_string::cap Current allocated capacity (in bytes, including room for
 *                    the trailing NUL).
 * @var s_string::len Current string length (in bytes, excluding the trailing
 *                    NUL).
 */
typedef struct s_string
{
	/** @brief Pointer to the allocated data
				(owned, NUL-terminated if cap > 0). */
	char	*data;
	/** @brief Current allocated capacity (in bytes). */
	size_t	cap;
	/** @brief Current length in bytes, excluding the trailing NUL. */
	size_t	len;
}	t_string;

/* --------------------------------- T_LIST -------------------------------- */

/**
 * @struct s_node
 * @brief Doubly linked list node structure.
 *
 * @var s_node::content Pointer to the node's content (owned by the node).
 * @var s_node::prev Pointer to the previous node (borrowed, may be NULL).
 * @var s_node::next Pointer to the next node (borrowed, may be NULL).
 */
typedef struct s_node
{
	/** @brief Pointer to the node's content (owned by the node). */
	void			*content;
	/** @brief Pointer to the previous node (borrowed, may be NULL). */
	struct s_node	*prev;
	/** @brief Pointer to the next node (borrowed, may be NULL). */
	struct s_node	*next;
}	t_node;

/**
 * @typedef t_list
 * @brief Type alias for a pointer to a list node (list head).
 */
typedef t_node	*t_list;

/* -------------------------------- T_BTREE -------------------------------- */

/**
 * @struct s_btree_node
 * @brief Binary tree node structure.
 *
 * @var s_btree_node::parent Pointer to the parent node (borrowed, may be NULL).
 * @var s_btree_node::left Pointer to the left child (borrowed, may be NULL).
 * @var s_btree_node::right Pointer to the right child (borrowed, may be NULL).
 * @var s_btree_node::data Pointer to node payload
 						   (owned by the node, may be NULL).
 */
typedef struct s_btree_node
{
	/** @brief Pointer to the parent node (borrowed, may be NULL). */
	struct s_btree_node	*parent;
	/** @brief Pointer to the left child (borrowed, may be NULL). */
	struct s_btree_node	*left;
	/** @brief Pointer to the right child (borrowed, may be NULL). */
	struct s_btree_node	*right;
	/** @brief Pointer to node payload (owned by the node, may be NULL). */
	void				*data;
}	t_btree_node;

/* -------------------------------- T_VECTOR ------------------------------- */

/**
 * @struct s_vector
 * @brief Dynamic array storing contiguous fixed-size items.
 *
 * The vector owns a single allocated memory block containing items stored
 * contiguously, with no gaps between them.
 *
 * @var s_vector::data Pointer to the allocated contiguous array of items
 *                     (owned by the vector, may be NULL).
 * @var s_vector::cap Current allocated capacity, expressed in items.
 * @var s_vector::len Current number of stored items, expressed in items.
 * @var s_vector::item_size Size of each item, expressed in bytes.
 */
typedef struct s_vector
{
	/** @brief Pointer to the allocated contiguous array of items
	*         (owned by the vector, may be NULL).
	*/
	void	*data;
	/** @brief Current allocated capacity, expressed in items. */
	size_t	cap;
	/** @brief Current number of stored items, expressed in items. */
	size_t	len;
	/** @brief Size of each item, expressed in bytes. */
	size_t	item_size;
}	t_vector;

/* ------------------------------- T_HASHMAP ------------------------------- */

/** @brief Default number of buckets allocated by hashmap_init(). */
# define HASHMAP_INIT_CAP	50

/**
 * @struct s_key_value
 * @brief Key/value pair stored inside a hashmap bucket.
 *
 * A pair owns a private copy of its key (duplicated on creation) and takes
 * ownership of the value pointer it is given. Both are released when the pair
 * is destroyed (the value through the map's del callback).
 *
 * @var s_key_value::key Heap-allocated copy of the key string (owned by the
 *                       pair).
 * @var s_key_value::value Pointer to the stored value (owned by the pair,
 *                         released through the map's del callback).
 */
typedef struct s_key_value
{
	/** @brief Heap-allocated copy of the key string (owned by the pair). */
	char	*key;
	/** @brief Pointer to the stored value (owned by the pair). */
	void	*value;
}	t_key_value;

/**
 * @struct s_hashmap
 * @brief Separate-chaining hash map keyed by NUL-terminated strings.
 *
 * Collisions are resolved by chaining key/value pairs into doubly linked lists
 * (one list per bucket). The bucket array is stored in a t_vector and grows
 * automatically when the number of stored pairs would exceed its capacity.
 *
 * @var s_hashmap::size Current number of stored key/value pairs.
 * @var s_hashmap::buckets Vector of t_list buckets, each a chain of
 *                         t_key_value pairs (owned by the map).
 * @var s_hashmap::hash Hash function applied to keys (defaults to
 *                      hash_string).
 * @var s_hashmap::del_value Optional destructor for stored values (may be
 *                           NULL, in which case values are never freed).
 */
typedef struct s_hashmap
{
	/** @brief Current number of stored key/value pairs. */
	size_t		size;
	/** @brief Vector of t_list buckets (owned by the map). */
	t_vector	buckets;
	/** @brief Hash function applied to keys (defaults to hash_string). */
	size_t		(*hash)(const char *key);
	/** @brief Optional destructor for stored values (may be NULL). */
	void		(*del_value)(void *);
}	t_hashmap;

/* ************************************************************************* */
/*                                   GROUPS                                  */
/* ************************************************************************* */

/** @defgroup btree Binary Tree API
 *  @brief Binary tree node utilities.
 *
 *  Functions to create, link, detach and recursively free binary tree nodes.
 */

/** @defgroup buff Buffer API
 *  @brief Dynamic growable buffer utilities.
 *
 *  Functions to initialize, grow, shrink and manipulate dynamic buffers.
 */

/** @defgroup chr Character Functions
 *  @brief Character classification and conversion.
 *
 *  Functions to test and transform individual characters.
 */

/** @defgroup conv Conversion Functions
 *  @brief String/number conversion utilities.
 *
 *  Functions to convert between strings and numeric types.
 */

/** @defgroup error Error Functions
 *  @brief Error reporting utilities.
 *
 *  Functions to print formatted error messages to stderr.
 */

/** @defgroup hashmap Hashmap API
 *  @brief String-keyed hash map with separate chaining.
 *
 *  Functions to create, populate, query and destroy a hash map that maps
 *  NUL-terminated string keys to arbitrary value pointers.
 */

/** @defgroup list Linked List API
 *  @brief Doubly linked list utilities.
 *
 *  Functions to create, manipulate and traverse doubly linked lists.
 */

/** @defgroup malloc Memory Allocation
 *  @brief Memory allocation utilities.
 *
 *  Functions for allocating and reallocating memory.
 */

/** @defgroup math Math Functions
 *  @brief Mathematical utilities.
 *
 *  Functions for common mathematical operations.
 */

/** @defgroup mem Memory Functions
 *  @brief Low-level memory operations.
 *
 *  Functions to manipulate raw memory blocks.
 */

/** @defgroup print Print Functions
 *  @brief Formatted output utilities.
 *
 *  Printf-like functions for formatted output to file descriptors.
 */

/** @defgroup put Put Functions
 *  @brief Basic output functions.
 *
 *  Functions to write characters, strings and numbers to file descriptors.
 */

/** @defgroup str String Functions
 *  @brief String manipulation utilities.
 *
 *  Functions to search, copy, compare and transform strings.
 */

/** @defgroup string Dynamic String API
 *  @brief NUL-terminated dynamic string utilities.
 *
 *  Functions to initialize, grow, shrink, read, format and manipulate
 *  dynamic strings whose allocated data is kept NUL-terminated.
 */

/** @defgroup vector Vector API
 *  @brief Dynamic array utilities for contiguous fixed-size items.
 *
 *  Functions to initialize, grow, shrink, duplicate and manipulate dynamic
 *  arrays storing items contiguously in memory.
 */

/* ************************************************************************* */
/*                                  BTREE                                    */
/* ************************************************************************* */

/**
 * @ingroup btree
 * @brief Creates a new binary tree node.
 *
 * @note Ownership of data is transferred to the new node on success.
 *       On failure, caller retains ownership of data.
 *
 * @param data Payload for the new node (ownership transferred on success).
 * @return Pointer to the new node (owned), or NULL on allocation failure.
 */
t_btree_node	*btree_new(void *data);

/**
 * @ingroup btree
 * @brief Sets the left child of a parent node.
 *
 * Links child under parent and updates child->parent accordingly.
 *
 * @warning parent and child must not be NULL.
 *
 * @param parent Parent node to update (borrowed).
 * @param child Child node to attach as left child (borrowed).
 */
void			btree_set_left(t_btree_node *parent, t_btree_node *child);

/**
 * @ingroup btree
 * @brief Sets the right child of a parent node.
 *
 * Links child under parent and updates child->parent accordingly.
 *
 * @warning parent and child must not be NULL.
 *
 * @param parent Parent node to update (borrowed).
 * @param child Child node to attach as right child (borrowed).
 */
void			btree_set_right(t_btree_node *parent, t_btree_node *child);

/**
 * @ingroup btree
 * @brief Detaches and returns the left child of a parent node.
 *
 * Updates both parent->left and the detached child's parent pointer to NULL.
 *
 * @warning parent and parent->left must not be NULL.
 *
 * @param parent Parent node to detach from (borrowed).
 * @return Detached left child node (owned by caller), or NULL if none.
 */
t_btree_node	*btree_detach_left(t_btree_node *parent);

/**
 * @ingroup btree
 * @brief Detaches and returns the right child of a parent node.
 *
 * Updates both parent->right and the detached child's parent pointer to NULL.
 *
 * @warning parent and parent->right must not be NULL.
 *
 * @param parent Parent node to detach from (borrowed).
 * @return Detached right child node (owned by caller), or NULL if none.
 */
t_btree_node	*btree_detach_right(t_btree_node *parent);

/**
 * @ingroup btree
 * @brief Recursively frees a node and its descendants.
 *
 * Performs a post-order traversal and frees each node. If data_free is
 * provided, it is called for each non-NULL node payload before node free.
 *
 * @param node Pointer to the root node pointer (set to NULL after freeing).
 * @param data_free Optional payload destructor (can be NULL).
 */
void			btree_free(t_btree_node **node, void (*data_free)(void *data));

/* ************************************************************************* */
/*                                   BUFF                                    */
/* ************************************************************************* */

/**
 * @ingroup buff
 * @brief Shrinks buffer capacity to match its current length.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_adjust(t_buff *buff);

/**
 * @ingroup buff
 * @brief Appends the content of a source buffer to the end of a buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning dst and src must be initialized before calling this function.
 *
 * @param dst Destination buffer to append to (borrowed).
 * @param src Source buffer to append (borrowed, read-only).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_append(t_buff *dst, const t_buff *src);

/**
 * @ingroup buff
 * @brief Appends formatted string to buffer using variadic arguments.
 *
 * > Supports printf formats:
 * `%%c` `%%s` `%%d` `%%i` `%%u` `%%x` `%%X` `%%p` `%%`.
 * > Supports printf-like flags: `-` `0` `.` ` ` `#` `+` and width.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fstring Format string (borrowed, read-only).
 * @param ... Variadic arguments for format specifiers.
 * @return true on success, false on failure.
 */
bool			buff_append_format(t_buff *buff, const char *fstring, ...)
				__attribute__((format(printf, 2, 3)));

/**
 * @ingroup buff
 * @brief Appends n first bytes of a string to the end of the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param b Pointer to an initialized buffer (borrowed).
 * @param str String to append (borrowed, read-only).
 * @param n Number of bytes to append, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_append_n(t_buff *b, const char *str, long n);

/**
 * @ingroup buff
 * @brief Appends formatted string to buffer using va_list.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fstring Format string (borrowed, read-only).
 * @param args Variable argument list.
 * @return true on success, false on failure.
 */
bool			buff_append_vformat(
					t_buff *buff,
					const char *fstring,
					va_list args);

/**
 * @ingroup buff
 * @brief Compares two buffers data byte by byte.
 *
 * @warning a and b must be initialized before calling this function.
 *
 * @param a First buffer to compare (borrowed, read-only).
 * @param b Second buffer to compare (borrowed, read-only).
 * @return true if the buffers have the same length and content, false
 *         otherwise.
 */
bool			buff_cmp(const t_buff *a, const t_buff *b);

/**
 * @ingroup buff
 * @brief Copies the content of a source buffer into an existing buffer.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning The previous logical content of dst is replaced, whether the
 *          function succeeds or fails.
 *
 * @param dst Destination buffer to overwrite (borrowed, initialized).
 * @param src Source buffer to duplicate (borrowed, initialized).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_dup(t_buff *dst, const t_buff *src);

/**
 * @ingroup buff
 * @brief Copies up to n bytes from a source buffer into an existing buffer.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning The previous logical content of dst is replaced, whether the
 *          function succeeds or fails.
 *
 * @param dst Destination buffer to overwrite (borrowed, initialized).
 * @param src Source buffer to duplicate (borrowed, initialized).
 * @param n Maximum number of bytes to copy.
 * @return true on success, false on memory allocation failure.
 */
bool			buff_dup_n(t_buff *dst, const t_buff *src, size_t n);

/**
 * @ingroup buff
 * @brief Frees the buffer's internal data.
 *
 * Sets buff->data to NULL after freeing.
 * Sets buff->len and buff->cap to 0 after freeing.
 *
 * @warning Does not free the t_buff struct itself, only its internal data.
 *
 * @param buff Pointer to the buffer (borrowed).
 */
void			buff_free(t_buff *buff);

/**
 * @ingroup buff
 * @brief Frees a t_buff item through a generic void* callback signature.
 *
 * Wrapper around buff_free() intended for APIs that expect
 * `void (*)(void *)`, such as vector_free().
 *
 * @warning buff must point to an initialized t_buff.
 * @warning Does not free the t_buff struct itself, only its internal data.
 *
 * @param buff Pointer to a t_buff item passed as void* (borrowed).
 */
void			buff_free_void(void *buff);

/**
 * @ingroup buff
 * @brief Finds the index of the first occurrence of a character in the buffer.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed, read-only).
 * @param c Character to find.
 * @return Index of the character, or -1 if not found.
 */
ssize_t			buff_get_index_c(const t_buff *buff, char c);

/**
 * @ingroup buff
 * @brief Finds the first occurrence of a substring in the buffer.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed, read-only).
 * @param s Substring to find (borrowed, read-only).
 * @param slen Number of bytes in s, or -1 to use str_len(s).
 * @return Index of the substring, or -1 if not found.
 */
ssize_t			buff_get_index_s(
					const t_buff *buff,
					const char *s,
					ssize_t slen);

/**
 * @ingroup buff
 * @brief Returns a newly allocated copy of the buffer content.
 *
 * If the buffer data is not null-terminated, a trailing '\0' is added in the
 * returned string.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @note Caller owns the returned string and must free it.
 * @note The caller remains owner of the t_buff.
 * @note The t_buff remains owner of the buff->data.
 *
 * @param buff Pointer to an initialized buffer (borrowed, read-only).
 * @return Newly allocated string (owned by caller), or NULL on failure.
 */
char			*buff_get_string(const t_buff *buff);

/**
 * @ingroup buff
 * @brief Initializes a buffer with the specified initial capacity.
 *
 * If str is not NULL, it is appended after initialization.
 * If str is NULL, n is ignored.
 *
 * @note Cannot fail only when initial_cap == 0 and str == NULL.
 *
 * @param buff Pointer to the buffer structure to initialize
 *			   (borrowed, uninitialized).
 * @param initial_cap Initial capacity of the buffer.
 * @param str Optional string to append after initialization
 			  (borrowed, read-only).
 * @param n Number of bytes to append, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_init(
					t_buff *buff,
					size_t initial_cap,
					const char *str,
					long n);

/**
 * @ingroup buff
 * @brief Inserts a source buffer in a buffer at the specified index.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning index must be in range [0, dst->len].
 *
 * @param dst Destination buffer to insert into (borrowed).
 * @param index Insertion index.
 * @param src Source buffer to insert (borrowed, read-only).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_insert(t_buff *dst, size_t index, const t_buff *src);

/**
 * @ingroup buff
 * @brief Inserts n first bytes of a string in the buffer at specified index.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning b must be initialized before calling this function.
 * @warning index must be in range [0, b->len].
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param b Pointer to an initialized buffer (borrowed).
 * @param index Insertion index.
 * @param str String to insert (borrowed, read-only).
 * @param n Number of bytes to insert, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_insert_n(t_buff *b, size_t index, const char *str, long n);

/**
 * @ingroup buff
 * @brief Prepends a source buffer to the beginning of a buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning dst and src must be initialized before calling this function.
 *
 * @param dst Destination buffer to prepend to (borrowed).
 * @param src Source buffer to prepend (borrowed, read-only).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_prepend(t_buff *dst, const t_buff *src);

/**
 * @ingroup buff
 * @brief Prepends n first bytes of a string to the beginning of the buffer.
 *
 * Buffer is automatically grown if necessary.
 *
 * @warning b must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param b Pointer to an initialized buffer (borrowed).
 * @param str String to prepend (borrowed, read-only).
 * @param n Number of bytes to prepend, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			buff_prepend_n(t_buff *b, const char *str, long n);

/**
 * @ingroup buff
 * @brief Reads all available data from a file descriptor into buffer.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, buff->data is NOT automatically freed.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @return true on success, false if read failed (totally or partially).
 */
bool			buff_read_all(t_buff *buff, int fd);

/**
 * @ingroup buff
 * @brief Reads from a file descriptor until a specific character is found.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, buff->data is NOT automatically freed.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @param c Character to search for.
 * @return true if c or EOF was encountered, false on memory or read error.
 */
bool			buff_read_until_c(t_buff *buff, int fd, char c);

/**
 * @ingroup buff
 * @brief Reads up to n bytes from a file descriptor into buffer.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, buff->data is NOT automatically freed.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @param n Number of bytes to read.
 * @return true on success or EOF, false on memory or read error.
 */
bool			buff_read_until_n(t_buff *buff, int fd, size_t n);

/**
 * @ingroup buff
 * @brief Reads from a file descriptor until a specific substring is found.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param fd File descriptor to read from.
 * @param s Target substring to search for (borrowed, read-only).
 * @param slen Length of s, or -1 to use str_len(s).
 * @return true if s or EOF was encountered, false on memory or read error.
 */
bool			buff_read_until_s(
					t_buff *buff,
					int fd,
					const char *s,
					ssize_t slen);

/**
 * @ingroup buff
 * @brief Removes a portion of the buffer starting at i_start.
 *
 * @note If len < 0, deletes all buffer content from i_start to end.
 *
 * @warning buff must be initialized before calling this function.
 *
 * @param buff Pointer to an initialized buffer (borrowed).
 * @param i_start Starting index for removal.
 * @param len Number of bytes to remove, or negative to remove until end.
 */
void			buff_rm_part(t_buff *buff, size_t i_start, ssize_t len);

/* ************************************************************************* */
/*                                   CHR                                     */
/* ************************************************************************* */

/**
 * @ingroup chr
 * @brief Checks if a character is alphanumeric.
 *
 * @param c Character to check.
 * @return Non-zero if alphanumeric, 0 otherwise.
 */
int				ft_isalnum(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is alphabetic.
 *
 * @param c Character to check.
 * @return Non-zero if alphabetic, 0 otherwise.
 */
int				ft_isalpha(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is a valid ASCII character (0-127).
 *
 * @param c Character to check.
 * @return Non-zero if ASCII, 0 otherwise.
 */
int				ft_isascii(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is a digit ('0'-'9').
 *
 * @param c Character to check.
 * @return Non-zero if digit, 0 otherwise.
 */
int				ft_isdigit(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is present in a character set.
 *
 * @param c Character to check.
 * @param charset Null-terminated string of characters to match against.
 * @return true if found in charset, false otherwise.
 */
bool			ft_isincharset(char c, const char *charset);

/**
 * @ingroup chr
 * @brief Checks if a character is printable (32-126).
 *
 * @param c Character to check.
 * @return Non-zero if printable, 0 otherwise.
 */
int				ft_isprint(int c);

/**
 * @ingroup chr
 * @brief Checks if a character is whitespace (9-13).
 *
 * @param c Character to check.
 * @return Non-zero if whitespace, 0 otherwise.
 */
int				ft_isspace(char c);

/**
 * @ingroup chr
 * @brief Converts an uppercase letter to lowercase.
 *
 * @param c Character to convert.
 * @return Lowercase equivalent if uppercase, otherwise unchanged.
 */
int				ft_tolower(int c);

/**
 * @ingroup chr
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c Character to convert.
 * @return Uppercase equivalent if lowercase, otherwise unchanged.
 */
int				ft_toupper(int c);

/* ************************************************************************* */
/*                                   CONV                                    */
/* ************************************************************************* */

/**
 * @ingroup conv
 * @brief Converts a string to an integer.
 *
 * @param str String to convert.
 * @return The converted integer value.
 */
int				ft_atoi(const char *str);

/**
 * @ingroup conv
 * @brief Converts a string to a long integer.
 *
 * @param str String to convert.
 * @return The converted long value.
 */
long			ft_atol(const char *str);

/**
 * @ingroup conv
 * @brief Converts a string to a pid_t.
 *
 * @param str String to convert.
 * @return The converted pid_t value.
 */
pid_t			ft_atopid(const char *str);

/**
 * @ingroup conv
 * @brief Converts a string to a size_t.
 *
 * @note Skips leading whitespace and accepts an optional leading '+'.
 * @warning Returns SIZE_MAX on overflow.
 *
 * @param str String to convert.
 * @return The converted size_t value.
 */
size_t			ft_atozu(const char *str);

/**
 * @ingroup conv
 * @brief Converts an integer to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Integer to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char			*ft_itoa(int n);

/**
 * @ingroup conv
 * @brief Converts an unsigned integer to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Unsigned integer to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char			*ft_utoa(unsigned int n);

/**
 * @ingroup conv
 * @brief Converts a size_t to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Value to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char			*ft_zutoa(size_t n);

/**
 * @ingroup conv
 * @brief Converts a long integer to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Long integer to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char			*ft_ltoa(long n);

/**
 * @ingroup conv
 * @brief Converts a pid_t to a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n pid_t value to convert.
 * @return Newly allocated string (owned), or NULL on failure.
 */
char			*ft_pidtoa(pid_t n);

/**
 * @ingroup conv
 * @brief Converts an unsigned long to a string in a given base.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param n Number to convert.
 * @param base String representing the base characters (borrowed, >= 2 chars).
 * @return Newly allocated string (owned), or NULL on failure.
 */
char			*ft_ultoa_base(unsigned long n, const char *base);

/**
 * @ingroup conv
 * @brief Parses a string to an integer with overflow detection.
 *
 * Accepts an optional leading '+' or '-' sign followed by digits.
 * Returns false if the string is empty, contains non-digit characters,
 * or the value would overflow an int.
 *
 * @param s String to parse (borrowed).
 * @param out Pointer to store the parsed integer (modified on success).
 * @return true on success, false if parsing failed or value out of range.
 */
bool			parse_int(char *s, int *out);

/* ************************************************************************* */
/*                                  ERROR                                    */
/* ************************************************************************* */

/**
 * @ingroup error
 * @brief Prints "Error\n" to stderr with optional message and errno.
 *
 * If print_errno is false and message is NULL, only "Error\n" is printed.
 * If print_errno is true, uses strerror() to print the errno description.
 * If message is not NULL, prints the message.
 * '\n' is always printed at the end.
 *
 * @param print_errno If true, prints errno description using strerror().
 * @param message Optional message to print (borrowed, can be NULL).
 */
void			print_err(bool print_errno, const char *message);

/**
 * @ingroup error
 * @brief Prints "Error\n" to stderr with safe prefix + formatted suffix.
 *
 * Prints safe prefix always, then attempts to format and append fmt.
 * If formatting fails, only the safe prefix is printed.
 * '\n' is always printed at the end.
 *
 * @warning safe and fmt must NOT be NULL, use print_err() otherwise.
 *
 * @param print_errno If true, prints errno description using strerror().
 * @param safe Safe prefix printed unconditionally (borrowed).
 * @param fmt Format string for suffix (borrowed).
 * @param ... Variadic arguments for format specifiers.
 */
void			fprint_err(
					bool print_errno,
					const char *safe,
					const char *fmt,
					...)
				__attribute__((format(printf, 3, 4)));

/* ************************************************************************* */
/*                                 HASHMAP                                   */
/* ************************************************************************* */

/**
 * @ingroup hashmap
 * @brief Initializes an empty hash map.
 *
 * Allocates the initial bucket array (HASHMAP_INIT_CAP buckets) and installs
 * the default string hash function. The del callback is stored as-is and used
 * to release stored values; the map does not own del itself.
 *
 * @note On failure the map is left in a zeroed state and must not be used.
 *
 * @param map Pointer to the map structure to initialize (uninitialized).
 * @param initial_cap Initial capacity of the bucket array.
 * @param del Optional destructor applied to each value on removal/free.
 *            Pass NULL to never free stored values.
 * @return true on success, false on memory allocation failure.
 */
bool			hashmap_init(
					t_hashmap *map,
					size_t initial_cap,
					void (*del)(void *));

/**
 * @ingroup hashmap
 * @brief Frees a hash map and all of its contents.
 *
 * Releases every stored pair: each key copy is freed, each value is passed to
 * the map's del callback (if any), and the bucket array is freed. The map is
 * reset to a zeroed state afterwards.
 *
 * @param map Pointer to the map to free (borrowed; reset to zero on return).
 */
void			hashmap_free(t_hashmap *map);

/**
 * @ingroup hashmap
 * @brief Inserts a key/value pair, replacing any existing value for the key.
 *
 * The key is duplicated internally, so the caller keeps ownership of the key
 * buffer. If the key already exists, its previous value is released through
 * the map's del callback before the new value takes its place. The bucket
 * array grows automatically when needed.
 *
 * @note On success, ownership of value is transferred to the map and is
 *       released through the del callback on removal or on hashmap_free().
 *
 * @note On failure, ownership of value remains with the caller.
 *
 * @note If key already exists and value is the same pointer as the currently
 *       stored value, hashmap_put() is a no-op and returns true.
 *
 * @warning When del is not NULL, each stored value pointer must have unique
 *          ownership. Storing the same owned pointer under several different
 *          keys can cause a double free on removal or hashmap_free().
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key (borrowed; duplicated internally).
 * @param value Value to associate with key (ownership transferred on success).
 * @return true on success, false on memory allocation failure.
 */
bool			hashmap_put(t_hashmap *map, const char *key, void *value);

/**
 * @ingroup hashmap
 * @brief Retrieves the value associated with a key.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key to look up (borrowed).
 * @return The associated value to the key (borrowed, still owned by the map),
 *         or NULL if the key is not present.
 */
void			*hashmap_get(t_hashmap *map, const char *key);

/**
 * @ingroup hashmap
 * @brief Collects every key/value pair stored in the map.
 *
 * Builds a freshly allocated, NULL-terminated array holding a pointer to each
 * of the map's size pairs, in unspecified (bucket) order.
 *
 * @note The returned array is owned by the caller and must be freed with a
 *       single free(). The pairs it points to are borrowed and remain owned by
 *       the map; do not free them and do not use the array after the map (or
 *       any referenced pair) has been modified or freed.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @return A NULL-terminated array of pair pointers (owned by caller), or NULL
 *         on memory allocation failure. The array is empty (only the NULL
 *         terminator) when the map holds no pairs.
 */
t_key_value		**hashmap_get_all(t_hashmap *map);

/**
 * @ingroup hashmap
 * @brief Removes the pair associated with a key.
 *
 * The matching pair is unlinked and freed: its key copy is freed and its value
 * is passed to the map's del callback (if any).
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key to remove (borrowed).
 * @return true if a pair was removed, false if the key was not found.
 */
bool			hashmap_remove(t_hashmap *map, const char *key);

/**
 * @ingroup hashmap
 * @brief Tests whether a key is present in the map.
 *
 * @param map Pointer to an initialized map (borrowed).
 * @param key NUL-terminated key to look for (borrowed).
 * @return true if the key is present, false otherwise.
 */
bool			hashmap_contains(t_hashmap *map, const char *key);

/**
 * @ingroup hashmap
 * @brief Allocates a key/value pair.
 *
 * Duplicates key into a private buffer and stores value by reference. The
 * caller therefore keeps ownership of the key buffer, while the new pair takes
 * ownership of value.
 *
 * @note On success, ownership of value is transferred to the pair. On failure,
 *       value is not retained and the caller keeps its ownership.
 *
 * @param key NUL-terminated key to copy (borrowed; duplicated internally).
 * @param value Value to store (ownership transferred on success).
 * @return Pointer to the new pair (owned by caller), or NULL on allocation
 *         failure.
 */
t_key_value		*key_value_new(const char *key, void *value);

/**
 * @ingroup hashmap
 * @brief Frees a key/value pair and its contents.
 *
 * Frees the duplicated key, passes the value to del (if provided) and frees
 * the pair itself. The caller's pointer is set to NULL. Safe to call with a
 * NULL pair pointer or a NULL pair.
 *
 * @param pair Address of the pair pointer to free (set to NULL on return).
 * @param del Optional destructor applied to the stored value (may be NULL).
 */
void			key_value_free(t_key_value **pair, void (*del)(void *));

/* ************************************************************************* */
/*                                   LIST                                    */
/* ************************************************************************* */

/**
 * @ingroup list
 * @brief Creates a new list node.
 *
 * @note Ownership of content is transferred to the node on success.
 *
 * @param content Content for the new node (ownership transferred).
 * @param prev Pointer to the previous node (borrowed, can be NULL).
 * @param next Pointer to the next node (borrowed, can be NULL).
 * @return Pointer to the new node (owned), or NULL on allocation failure.
 */
t_node			*node_new(void *content, t_node *prev, t_node *next);

/**
 * @ingroup list
 * @brief Frees a node and optionally its content.
 *
 * @param node Pointer to the node pointer (set to NULL after freeing).
 * @param del_content Function to delete the content (can be NULL to skip).
 */
void			node_free(t_node **node, void (*del_content)(void*));

/**
 * @ingroup list
 * @brief Adds a new element at the end of the list.
 *
 * @note Ownership of new_content is transferred to the list on success.
 *       On failure, caller retains ownership of new_content.
 *
 * @param list Pointer to the list pointer (borrowed).
 * @param new_content Content for the new node (ownership transferred).
 * @return true on success, false on allocation failure.
 */
bool			list_add_end(t_list *list, void *new_content);

/**
 * @ingroup list
 * @brief Adds a new element at the start of the list.
 *
 * @note Ownership of new_content is transferred to the list on success.
 *       On failure, caller retains ownership of new_content.
 *
 * @param list Pointer to the list pointer (borrowed).
 * @param new_content Content for the new node (ownership transferred).
 * @return true on success, false on allocation failure.
 */
bool			list_add_start(t_list *list, void *new_content);

/**
 * @ingroup list
 * @brief Calculates the number of nodes in the list.
 *
 * @param list List to count.
 * @return Number of nodes in the list.
 */
size_t			list_get_size(t_list list);

/**
 * @ingroup list
 * @brief Finds content in list matching a selection function.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @param select_function Function returning true for desired content.
 * @return Matching content (borrowed), or NULL if not found.
 */
void			*list_get_content(t_list list, bool (*select_function)(void*));

/**
 * @ingroup list
 * @brief Gets content at a specific index in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @param index Zero-based index.
 * @return Content at index (borrowed), or NULL if index out of bounds.
 */
void			*list_get_content_n(t_list list, size_t index);

/**
 * @ingroup list
 * @brief Gets the content of the last node in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @return Content of last node (borrowed), or NULL if list is empty.
 */
void			*list_get_content_last(t_list list);

/**
 * @ingroup list
 * @brief Gets the node at a specific index in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @param index Zero-based index.
 * @return Node at index (borrowed), or NULL if index out of bounds.
 */
t_node			*list_get_node_n(t_list list, size_t index);

/**
 * @ingroup list
 * @brief Gets the last node in the list.
 *
 * @note Returned pointer is borrowed from the list. Do not free it directly;
 *       the list retains ownership. Pointer becomes invalid if node is removed.
 *
 * @param list List to search (borrowed).
 * @return Last node (borrowed), or NULL if list is empty.
 */
t_node			*list_get_node_last(t_list list);

/**
 * @ingroup list
 * @brief Applies a function to each element of the list.
 *
 * @param lst List to iterate over (borrowed).
 * @param f Function to apply to each element's content.
 */
void			list_iter(t_list lst, void (*f)(void *));

/**
 * @ingroup list
 * @brief Creates a new list by applying a function to each element.
 *
 * @note Caller owns the returned list and must free it with list_rm_all.
 *
 * @param list Source list (borrowed).
 * @param f Function to apply to each element (returns new content, owned).
 * @param del Function to delete content on failure.
 * @return New list (owned), or NULL on failure.
 */
t_list			list_map(t_list list, void *(*f)(void *), void (*del)(void *));

/**
 * @ingroup list
 * @brief Removes a specific node from the list.
 *
 * @param list Pointer to the list pointer (borrowed).
 * @param node Node to remove (ownership taken, will be freed).
 * @param del_content Function to delete the node's content (can be NULL).
 */
void			list_rm(t_list *list, t_node *node, void (*del_content)(void*));

/**
 * @ingroup list
 * @brief Removes all nodes from the list.
 *
 * @param list Pointer to the list pointer (set to NULL after).
 * @param del_content Function to delete each node's content (can be NULL).
 */
void			list_rm_all(t_list *list, void (*del_content)(void*));

/* ************************************************************************* */
/*                                  MALLOC                                   */
/* ************************************************************************* */

/**
 * @ingroup malloc
 * @brief Allocates and zeroes memory for an array.
 *
 * @note Caller owns the returned memory and must free it.
 *
 * @param count Number of elements.
 * @param size Size of each element.
 * @return Pointer to allocated zeroed memory (owned), or NULL on failure.
 */
void			*ft_calloc(size_t count, size_t size);

/**
 * @ingroup malloc
 * @brief Reallocates a buffer to a new capacity.
 *
 * @note If newcap is 0, *buff is freed and set to NULL.
 *
 * @param buff Pointer to the buffer pointer (owned, reallocated in place).
 * @param cap Current capacity.
 * @param newcap New capacity (0 to free the buffer).
 * @return true on success, false on failure (original buffer unchanged).
 */
bool			ft_realloc(char **buff, size_t cap, size_t newcap);

/* ************************************************************************* */
/*                                   MATH                                    */
/* ************************************************************************* */

/**
 * @ingroup math
 * @brief Returns the minimum of two long integers.
 *
 * @param a First long integer.
 * @param b Second long integer.
 * @return The smaller value.
 */
long			min(long a, long b);

/**
 * @ingroup math
 * @brief Returns the maximum of two long integers.
 *
 * @param a First long integer.
 * @param b Second long integer.
 * @return The larger value.
 */
long			max(long a, long b);

/**
 * @ingroup math
 * @brief Returns the absolute value of a long integer.
 *
 * @param nbr Number to get absolute value of.
 * @return Absolute value as size_t (always positive).
 */
size_t			absolute(long nbr);

/**
 * @ingroup math
 * @brief Computes a raised to the power of b.
 *
 * Uses bit shifting optimization when a == 2.
 *
 * @warning UB if the result overflows a long.
 * @warning Returns 0 for negative exponents (cannot represent fractions).
 *
 * @param a Base value.
 * @param b Exponent (must be >= 0 for meaningful result).
 * @return a^b, or 0 if b < 0.
 */
long			power(int a, int b);

/**
 * @ingroup math
 * @brief Computes the modulo of a signed integer with an unsigned modulus.
 *
 * Handles negative values of a by ensuring the result is always positive.
 *
 * @param a Dividend (can be negative).
 * @param b Divisor (must be > 0).
 * @return Remainder in range [0, b-1].
 */
size_t			modulo(long a, size_t b);

/**
 * @ingroup math
 * @brief Calculates the exact integer square root.
 *
 * @param nb Number to find square root of.
 * @return Exact square root if nb is a perfect square, -1 otherwise.
 */
int				square_root_exact(int nb);

/**
 * @ingroup math
 * @brief Calculates the nearest integer square root.
 *
 * @param nb Number to find square root of.
 * @return Nearest integer square root, -1 if nb <= 0.
 */
int				square_root_rounded(int nb);

/* ************************************************************************* */
/*                                   MEM                                     */
/* ************************************************************************* */

/**
 * @ingroup mem
 * @brief Sets n bytes of memory to zero.
 *
 * @param s Pointer to memory area.
 * @param n Number of bytes to set.
 */
void			ft_bzero(void *s, size_t n);

/**
 * @ingroup mem
 * @brief Locates the first occurrence of a byte in memory.
 *
 * @note Returned pointer is borrowed from s. Do not free it directly.
 *
 * @param s Memory area to search (borrowed).
 * @param c Byte to search for (converted to unsigned char).
 * @param n Number of bytes to search.
 * @return Pointer to the byte (borrowed), or NULL if not found.
 */
void			*ft_memchr(const void *s, int c, size_t n);

/**
 * @ingroup mem
 * @brief Compares two memory areas byte by byte.
 *
 * @param s1 First memory area.
 * @param s2 Second memory area.
 * @param n Number of bytes to compare.
 * @return Difference of first differing bytes, or 0 if equal.
 */
int				ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @ingroup mem
 * @brief Copies n bytes from src to dst.
 *
 * @warning Memory areas must not overlap. Use ft_memmove for overlapping.
 *
 * @param dst Destination memory area (borrowed).
 * @param src Source memory area (borrowed).
 * @param n Number of bytes to copy.
 * @return Pointer to dst.
 */
void			*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @ingroup mem
 * @brief Copies n bytes from src to dst, handling overlapping memory.
 *
 * @param dst Destination memory area.
 * @param src Source memory area.
 * @param len Number of bytes to copy.
 * @return Pointer to dst.
 */
void			*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @ingroup mem
 * @brief Fills memory with a constant byte.
 *
 * @param b Memory area to fill.
 * @param c Byte value to set (converted to unsigned char).
 * @param len Number of bytes to set.
 * @return Pointer to b.
 */
void			*ft_memset(void *b, int c, size_t len);

/* ************************************************************************* */
/*                                  PRINT                                    */
/* ************************************************************************* */

/**
 * @ingroup print
 * @brief Writes formatted output to a file descriptor using va_list.
 *
 * @param fd File descriptor to write to.
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return Number of bytes written, or -1 on error.
 */
int				ft_vdprintf(int fd, const char *fstring, va_list args);

/**
 * @ingroup print
 * @brief Writes formatted output to a file descriptor.
 *
 * > Supports printf formats: 
 * `%%c` `%%s` `%%d` `%%i` `%%u` `%%x` `%%X` `%%p` `%%`.  
 * > Supports printf-like flags: `-` `0` `.` ` ` `#` `+` and width.
 *
 * @param fd File descriptor to write to.
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return Number of bytes written, or -1 on error.
 */
int				ft_dprintf(int fd, const char *fstring, ...)
				__attribute__((format(printf, 2, 3)));

/**
 * @ingroup print
 * @brief Writes formatted output to stdout using va_list.
 *
 * @param fstring Format string.
 * @param args Variable argument list.
 * @return Number of bytes written, or -1 on error.
 */
int				ft_vprintf(const char *fstring, va_list args);

/**
 * @ingroup print
 * @brief Writes formatted output to stdout.
 *
 * > Supports printf formats: 
 * `%%c` `%%s` `%%d` `%%i` `%%u` `%%x` `%%X` `%%p` `%%`.  
 * > Supports printf-like flags: `-` `0` `.` ` ` `#` `+` and width.
 *
 * @param fstring Format string.
 * @param ... Variadic arguments for format specifiers.
 * @return Number of bytes written, or -1 on error.
 */
int				ft_printf(const char *fstring, ...)
				__attribute__((format(printf, 1, 2)));

/* ************************************************************************* */
/*                                   PUT                                     */
/* ************************************************************************* */

/**
 * @brief Writes a character to a file descriptor.
 *
 * @param c Character to write.
 * @param fd File descriptor to write to.
 */
void			ft_putchar_fd(char c, int fd);

/**
 * @ingroup put
 * @brief Writes a string followed by newline to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void			ft_putendl_fd(char *s, int fd);

/**
 * @ingroup put
 * @brief Writes an integer to a file descriptor.
 *
 * @param n Integer to write.
 * @param fd File descriptor to write to.
 */
void			ft_putnbr_fd(int n, int fd);

/**
 * @ingroup put
 * @brief Writes a string to a file descriptor.
 *
 * @param s String to write (NULL prints "(null)").
 * @param fd File descriptor to write to.
 */
void			ft_putstr_fd(char *s, int fd);

/* ************************************************************************* */
/*                                   STR                                     */
/* ************************************************************************* */

/**
 * @brief Frees all strings in a null-terminated array and the tab itself.
 *
 * @note The tab is set at NULL after beeing freed.
 *
 * @param tab Array of strings to free.
 */
void			str_array_free(char ***tab_ptr);

/**
 * @ingroup str
 * @brief Locates the first occurrence of a character in a string.
 *
 * @note Returned pointer is borrowed from s. Do not free it directly.
 * @note If c is '\\0', returns pointer to the terminating null.
 *
 * @param s String to search (borrowed).
 * @param c Character to find.
 * @return Pointer to the character (borrowed), or NULL if not found.
 */
char			*str_chr(const char *s, int c);

/**
 * @ingroup str
 * @brief Compares two strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @return Difference of first differing characters, or 0 if equal.
 */
int				str_cmp(const char *s1, const char *s2);

/**
 * @brief Counts words in a string separated by a delimiter.
 *
 * @param s String to analyze.
 * @param sep Delimiter character.
 * @return Number of words.
 */
size_t			str_count_words(char const *s, char sep);

/**
 * @ingroup str
 * @brief Duplicates a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s1 String to duplicate (borrowed).
 * @return Newly allocated copy (owned), or NULL on failure.
 */
char			*str_dup(const char *s1);

/**
 * @ingroup str
 * @brief Applies a function to each character of a string with its index.
 *
 * @param s String to iterate (modified in place).
 * @param f Function taking index and character pointer.
 */
void			str_iteri(char *s, void (*f)(unsigned int, char*));

/**
 * @ingroup str
 * @brief Concatenates two strings into a new string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s1 First string (borrowed).
 * @param s2 Second string (borrowed).
 * @return Newly allocated concatenated string (owned), or NULL on failure.
 */
char			*str_join(char const *s1, char const *s2);

/**
 * @ingroup str
 * @brief Appends src to dst with size limit.
 *
 * @param dst Destination buffer (must be null-terminated).
 * @param src Source string.
 * @param dstsize Total size of destination buffer.
 * @return Total length of string it tried to create.
 */
size_t			str_lcat(char *dst, const char *src, size_t dstsize);

/**
 * @ingroup str
 * @brief Copies src to dst with size limit.
 *
 * @param dst Destination buffer.
 * @param src Source string.
 * @param dstsize Size of destination buffer.
 * @return Length of src.
 */
size_t			str_lcpy(char *dst, const char *src, size_t dstsize);

/**
 * @ingroup str
 * @brief Calculates the length of a string.
 *
 * @param s String to measure.
 * @return Length of the string (not including null terminator).
 */
size_t			str_len(const char *s);

/**
 * @ingroup str
 * @brief Creates a new string by applying a function to each character.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s String to transform (borrowed).
 * @param f Function taking index and character, returning new character.
 * @return Newly allocated transformed string (owned), or NULL on failure.
 */
char			*str_mapi(char const *s, char (*f)(unsigned int, char));

/**
 * @ingroup str
 * @brief Compares at most n characters of two strings.
 *
 * @param s1 First string.
 * @param s2 Second string.
 * @param n Maximum number of characters to compare.
 * @return Difference of first differing characters, or 0 if equal.
 */
int				str_ncmp(const char *s1, const char *s2, size_t n);

/**
 * @ingroup str
 * @brief Duplicates the first len bytes of a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param src String to duplicate (borrowed).
 * @param len Maximum number of bytes to copy.
 * @return Newly allocated copy (owned), or NULL on failure.
 */
char			*str_ndup(const char *src, size_t len);

/**
 * @ingroup str
 * @brief Locates a substring within a string, limited by length.
 *
 * @note Returned pointer is borrowed from haystack. Do not free it directly.
 *
 * @param haystack String to search in (borrowed).
 * @param needle Substring to find (borrowed).
 * @param len Maximum characters to search.
 * @return Pointer to start of substring (borrowed), or NULL if not found.
 */
char			*str_nstr(const char *haystack, const char *needle, size_t len);

/**
 * @ingroup str
 * @brief Locates the last occurrence of a character in a string.
 *
 * @note Returned pointer is borrowed from s. Do not free it directly.
 * @note If c is '\\0', returns pointer to the terminating null.
 *
 * @param s String to search (borrowed).
 * @param c Character to find.
 * @return Pointer to the character (borrowed), or NULL if not found.
 */
char			*str_rchr(const char *s, int c);

/**
 * @ingroup str
 * @brief Splits a string into an array of strings using a delimiter.
 *
 * @note Caller owns the returned array and each string within it.
 *       Free each string then free the array itself.
 *
 * @param s String to split (borrowed).
 * @param c Delimiter character.
 * @return NULL-terminated array of strings (owned), or NULL on failure.
 */
char			**str_split(char const *s, char c);

/**
 * @ingroup str
 * @brief Extracts a substring from a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s Source string (borrowed).
 * @param start Starting index.
 * @param len Maximum length of substring.
 * @return Newly allocated substring (owned), or NULL on failure.
 */
char			*str_sub(char const *s, unsigned int start, size_t len);

/**
 * @ingroup str
 * @brief Trims characters from the beginning and end of a string.
 *
 * @note Caller owns the returned string and must free it.
 *
 * @param s1 String to trim (borrowed).
 * @param set Characters to trim (borrowed).
 * @return Newly allocated trimmed string (owned), or NULL on failure.
 */
char			*str_trim(char const *s1, char const *set);

char			*str_trim_leading(char const *s1, char const *set);

/* ************************************************************************* */
/*                                  STRING                                   */
/* ************************************************************************* */

/**
 * @ingroup string
 * @brief Shrinks string capacity to match its current length plus NUL byte.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @return true on success, false on memory allocation failure.
 */
bool			string_adjust(t_string *string);

/**
 * @ingroup string
 * @brief Appends the content of a source string to the end of a string.
 *
 * Destination storage is automatically grown if necessary.
 *
 * @warning dst and src must be initialized before calling this function.
 *
 * @param dst Destination string to append to (borrowed).
 * @param src Source string to append (borrowed, read-only).
 * @return true on success, false on memory allocation failure.
 */
bool			string_append(t_string *dst, const t_string *src);

/**
 * @ingroup string
 * @brief Appends formatted text to string using variadic arguments.
 *
 * > Supports the same format subset as buff_append_format().
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fstring Format string (borrowed, read-only).
 * @param ... Variadic arguments for format specifiers.
 * @return true on success, false on failure.
 */
bool			string_append_format(t_string *string, const char *fstring, ...)
				__attribute__((format(printf, 2, 3)));

/**
 * @ingroup string
 * @brief Appends n first bytes of a string to the end of a dynamic string.
 *
 * Destination storage is automatically grown if necessary.
 *
 * @warning s must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param s Destination string to append to (borrowed).
 * @param str String to append (borrowed, read-only).
 * @param n Number of bytes to append, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			string_append_n(t_string *s, const char *str, long n);

/**
 * @ingroup string
 * @brief Appends formatted text to string using va_list.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fstring Format string (borrowed, read-only).
 * @param args Variable argument list.
 * @return true on success, false on failure.
 */
bool			string_append_vformat(
					t_string *string,
					const char *fstring,
					va_list args);

/**
 * @ingroup string
 * @brief Compares two strings byte by byte.
 *
 * @warning a and b must be initialized before calling this function.
 *
 * @param a First string to compare (borrowed, read-only).
 * @param b Second string to compare (borrowed, read-only).
 * @return true if the strings have the same length and content, false
 *         otherwise.
 */
bool			string_cmp(const t_string *a, const t_string *b);

/**
 * @ingroup string
 * @brief Copies the content of a source string into an existing string.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning The previous logical content of dst is replaced, whether the
 *          function succeeds or fails.
 *
 * @param dst Destination string to overwrite
 *            (borrowed, initialized by the function).
 * @param src Source string to duplicate (borrowed, initialized).
 * @return true on success, false on memory allocation failure.
 */
bool			string_dup(t_string *dst, const t_string *src);

/**
 * @ingroup string
 * @brief Copies up to n bytes from a source string into an existing string.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning The previous logical content of dst is replaced, whether the
 *          function succeeds or fails.
 *
 * @param dst Destination string to overwrite
 *            (borrowed, initialized by the function).
 * @param src Source string to duplicate (borrowed, initialized).
 * @param n Maximum number of bytes to copy.
 * @return true on success, false on memory allocation failure.
 */
bool			string_dup_n(t_string *dst, const t_string *src, size_t n);

/**
 * @ingroup string
 * @brief Frees the string's internal data.
 *
 * Sets string->data to NULL after freeing.
 * Sets string->len and string->cap to 0 after freeing.
 *
 * @warning Does not free the t_string struct itself, only its internal data.
 *
 * @param string Pointer to the string (borrowed).
 */
void			string_free(t_string *string);

/**
 * @ingroup string
 * @brief Frees a t_string item through a generic void* callback signature.
 *
 * Wrapper around string_free() intended for APIs that expect
 * `void (*)(void *)`, such as vector_free().
 *
 * @warning string must point to an initialized t_string.
 * @warning Does not free the t_string struct itself, only its internal data.
 *
 * @param string Pointer to a t_string item passed as void* (borrowed).
 */
void			string_free_void(void *string);

/**
 * @ingroup string
 * @brief Finds the index of the first occurrence of a character in the string.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed, read-only).
 * @param c Character to find.
 * @return Index of the character, or -1 if not found.
 */
ssize_t			string_get_index_c(const t_string *string, char c);

/**
 * @ingroup string
 * @brief Finds the first occurrence of a substring in the string.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed, read-only).
 * @param s Substring to find (borrowed, read-only).
 * @param slen Number of bytes in s, or -1 to use str_len(s).
 * @return Index of the substring, or -1 if not found.
 */
ssize_t			string_get_index_s(
					const t_string *string,
					const char *s,
					ssize_t slen);

/**
 * @ingroup string
 * @brief Initializes a string with the specified initial capacity.
 *
 * If str is not NULL, it is appended after initialization.
 * If str is NULL, n is ignored.
 *
 * @note Cannot fail only when initial_cap == 0 and str == NULL.
 *
 * @warning When initial_cap == 0 and str == NULL, no allocation is performed:
 *          data is NULL and cannot be used as a valid C string until a
 *          function that allocates storage has been called.
 *
 * @param s Pointer to the string structure to initialize
 *          (borrowed, uninitialized).
 * @param initial_cap Initial capacity of the string.
 * @param str Optional string to append after initialization
 *            (borrowed, read-only).
 * @param n Number of bytes to append, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			string_init(
					t_string *s,
					size_t initial_cap,
					const char *str,
					long n);

/**
 * @ingroup string
 * @brief Inserts a source string in a string at the specified index.
 *
 * Destination storage is automatically grown if necessary.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning index must be in range [0, dst->len].
 *
 * @param dst Destination string to insert into (borrowed).
 * @param index Insertion index.
 * @param src Source string to insert (borrowed, read-only).
 * @return true on success, false on memory allocation failure.
 */
bool			string_insert(t_string *dst, size_t index, const t_string *src);

/**
 * @ingroup string
 * @brief Inserts n first bytes of a string at the specified index.
 *
 * Destination storage is automatically grown if necessary.
 *
 * @warning s must be initialized before calling this function.
 * @warning index must be in range [0, s->len].
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param s Destination string to insert into (borrowed).
 * @param index Insertion index.
 * @param str String to insert (borrowed, read-only).
 * @param n Number of bytes to insert, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			string_insert_n(
					t_string *s,
					size_t index,
					const char *str,
					long n);

/**
 * @ingroup string
 * @brief Prepends a source string to the beginning of a string.
 *
 * Destination storage is automatically grown if necessary.
 *
 * @warning dst and src must be initialized before calling this function.
 *
 * @param dst Destination string to prepend to (borrowed).
 * @param src Source string to prepend (borrowed, read-only).
 * @return true on success, false on memory allocation failure.
 */
bool			string_prepend(t_string *dst, const t_string *src);

/**
 * @ingroup string
 * @brief Prepends n first bytes of a string to the beginning of a string.
 *
 * Destination storage is automatically grown if necessary.
 *
 * @warning s must be initialized before calling this function.
 * @warning UB if n > 0 and str is shorter than n bytes.
 *
 * @param s Destination string to prepend to (borrowed).
 * @param str String to prepend (borrowed, read-only).
 * @param n Number of bytes to prepend, or -1 to use str_len(str).
 * @return true on success, false on memory allocation failure.
 */
bool			string_prepend_n(t_string *s, const char *str, long n);

/**
 * @ingroup string
 * @brief Reads all available data from a file descriptor into string.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, string->data is NOT automatically freed.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fd File descriptor to read from.
 * @return true on success, false if read failed.
 */
bool			string_read_all(t_string *string, int fd);

/**
 * @ingroup string
 * @brief Reads from a file descriptor until a specific character is found.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, string->data is NOT automatically freed.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fd File descriptor to read from.
 * @param c Character to search for.
 * @return true if c or EOF was encountered, false on memory or read error.
 */
bool			string_read_until_c(t_string *string, int fd, char c);

/**
 * @ingroup string
 * @brief Reads up to n bytes from a file descriptor into string.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, string->data is NOT automatically freed.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fd File descriptor to read from.
 * @param n Number of bytes to read.
 * @return true on success or EOF, false on memory or read error.
 */
bool			string_read_until_n(t_string *string, int fd, size_t n);

/**
 * @ingroup string
 * @brief Reads from a file descriptor until a specific substring is found.
 *
 * @note Interrupted reads (EINTR) are retried.
 * @note On failure, string->data is NOT automatically freed.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param fd File descriptor to read from.
 * @param s Target substring to search for (borrowed, read-only).
 * @param slen Length of s, or -1 to use str_len(s).
 * @return true if s or EOF was encountered, false on memory or read error.
 */
bool			string_read_until_s(
					t_string *string,
					int fd,
					const char *s,
					ssize_t slen);

/**
 * @ingroup string
 * @brief Removes a portion of the string starting at i_start.
 *
 * @note If len < 0, deletes all string content from i_start to end.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string Pointer to an initialized string (borrowed).
 * @param i_start Starting index for removal.
 * @param len Number of bytes to remove, or negative to remove until end.
 */
void			string_rm_part(t_string *string, size_t i_start, ssize_t len);

/**
 * @ingroup string
 * @brief Splits a string into two initialized strings at a byte index.
 *
 * @note @p out_before and @p out_after are initialized by the function.
 * @note When @p index is greater than or equal to @p src->len, @p out_before
 *       receives a full copy of @p src and @p out_after is initialized empty.
 *
 * @warning @p src must be initialized before calling this function.
 * @warning @p out_before and @p out_after must not already own allocated data.
 *
 * @param src Source string to split (borrowed, read-only).
 * @param index Split index.
 * @param out_before Destination receiving the bytes before @p index
 *                   (borrowed, initialized by the function).
 * @param out_after Destination receiving the bytes starting at @p index
 *                  (borrowed, initialized by the function).
 * @return true on success, false on memory allocation failure.
 */
bool			string_split_at(
					const t_string *src,
					size_t index,
					t_string *out_before,
					t_string *out_after);

/**
 * @ingroup string
 * @brief Splits a string on a delimiter character into a @ref t_vector.
 *
 * Empty fields are kept when @p keep_empty_entries is @c true and skipped
 * when it is @c false.
 *
 * @note @p out is initialized by the function with @c sizeof(t_string) items.
 * @note When @p keep_empty_entries is @c true and @p src is empty, @p out
 *       receives one empty @ref t_string.
 * @note On failure, the function frees every initialized item and resets
 *       @p out.
 *
 * @warning @p src must be initialized before calling this function.
 * @warning @p out must not already own allocated data.
 *
 * @param src Source string to split (borrowed, read-only).
 * @param c Delimiter character.
 * @param keep_empty_entries True to keep empty fields, false to drop them.
 * @param out Destination vector receiving initialized @ref t_string items
 *            (borrowed, initialized by the function).
 * @return true on success, false on memory allocation failure.
 */
bool			string_split_on_char(
					const t_string *src,
					char c,
					bool keep_empty_entries,
					t_vector *out);

/**
 * @ingroup string
 * @brief Splits a string on a delimiter C-string into a @ref t_vector.
 *
 * Empty fields are kept when @p keep_empty_entries is @c true and skipped
 * when it is @c false.
 *
 * @note @p out is initialized by the function with @c sizeof(t_string) items.
 * @note When @p sep is empty and @p keep_empty_entries is @c true, @p out
 *       receives one item containing a full copy of @p src.
 * @note When @p sep is empty and @p keep_empty_entries is @c false, @p out
 *       receives one item only if @p src is not empty.
 * @note On failure, the function frees every initialized item and resets
 *       @p out.
 *
 * @warning @p src must be initialized before calling this function.
 * @warning @p sep must point to a valid NUL-terminated C-string.
 * @warning @p out must not already own allocated data.
 *
 * @param src Source string to split (borrowed, read-only).
 * @param sep Delimiter C-string (borrowed, read-only).
 * @param keep_empty_entries True to keep empty fields, false to drop them.
 * @param out Destination vector receiving initialized @ref t_string items
 *            (borrowed, initialized by the function).
 * @return true on success, false on memory allocation failure.
 */
bool			string_split_on_string(
					const t_string *src,
					const char *sep,
					bool keep_empty_entries,
					t_vector *out);

/**
 * @ingroup string
 * @brief Takes ownership of an existing buffer and installs it in a string.
 *
 * The buffer is not copied. The string structure is updated to reference the
 * provided storage directly.
 *
 * @warning dst must point to an initialized t_string.
 * @warning src becomes owned by dst on success and must not be freed by the
 *          caller afterwards.
 *
 * @param dst Destination string to update (borrowed).
 * @param src Buffer to take ownership of (ownership transferred).
 * @param cap Capacity of src, in bytes.
 * @param len Logical length of the string stored in src or -1 tu use str_len().
 */
void			string_take(t_string *dst, char *src, size_t cap, ssize_t len);

/**
 * @ingroup string
 * @brief Removes leading copies of a character from a string.
 *
 * @note The string is modified in place and no allocation is performed.
 *
 * @warning string must be initialized before calling this function.
 *
 * @param string String to trim (borrowed).
 * @param c Character to remove.
 */
void			string_trim_leading(t_string *string, char c);

/* ************************************************************************* */
/*                                  VECTOR                                   */
/* ************************************************************************* */

/**
 * @ingroup vector
 * @brief Initializes a vector with a given item size and initial capacity.
 *
 * @note Cannot fail when cap == 0.
 *
 * @warning vector must NOT already own allocated data. Call vector_free()
 *          first if needed.
 *
 * @param vector Pointer to the vector to initialize (borrowed, uninitialized).
 * @param item_size Size of each item, in bytes (must be > 0).
 * @param cap Initial capacity, expressed in items.
 * @return true on success, false on invalid item_size, overflow, or allocation
 *         failure.
 */
bool			vector_init(t_vector *vector, size_t item_size, size_t cap);

/**
 * @ingroup vector
 * @brief Grows vector capacity, usually by doubling it.
 *
 * Existing items are preserved. If current capacity is 0, grows to
 * VECTOR_INIT_CAP.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @return true on success, false on overflow or allocation failure.
 */
bool			vector_grow(t_vector *vector);

/**
 * @ingroup vector
 * @brief Shrinks vector capacity to match its current length.
 *
 * Existing items are preserved. If vector length is 0, internal storage is
 * freed.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @return true on success, false on allocation failure.
 */
bool			vector_adjust(t_vector *vector);

/**
 * @ingroup vector
 * @brief Duplicates a vector into another one.
 *
 * A new internal storage is allocated for dst. Items are copied byte-for-byte;
 * item payloads themselves are not deep-copied.
 *
 * @note On success, dst is initialized and owns its internal storage.
 *       Caller must later release it with vector_free().
 *
 * @warning dst must NOT be initialized, or must be freed before calling this
 *          function.
 * @warning dst and src must be different.
 *
 * @param dst Destination vector to initialize and fill (borrowed).
 * @param src Source vector to duplicate (borrowed).
 * @return true on success, false on failure.
 */
bool			vector_dup(t_vector *dst, t_vector *src);

/**
 * @ingroup vector
 * @brief Frees the vector's internal storage.
 *
 * Sets vector->data to NULL after freeing.
 * Sets vector->len and vector->cap to 0 after freeing.
 *
 * @warning Does not free the t_vector struct itself, only its internal data.
 *
 * @param vector Pointer to the vector (borrowed).
 * @param item_free Optional callback to free each item (can be NULL).
 */
void			vector_free(t_vector *vector, void (*item_free)(void *item));

/**
 * @ingroup vector
 * @brief Appends one item at the end of the vector.
 *
 * Vector is automatically grown if necessary.
 *
 * @warning vector must be initialized before calling this function.
 * @warning item must NOT point inside vector->data.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param item Item to append (borrowed, not modified).
 * @return true on success, false on allocation failure.
 */
bool			vector_push(t_vector *vector, const void *item);

/**
 * @ingroup vector
 * @brief Removes the last item from the vector.
 *
 * If dst is not NULL, the removed item is copied there before removal.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param dst Optional destination buffer receiving the removed item (borrowed,
 *            can be NULL).
 * @return true on success, false if the vector is empty.
 */
bool			vector_pop(t_vector *vector, void *dst);

/**
 * @ingroup vector
 * @brief Inserts one item at a specific index.
 *
 * Existing items at and after index are shifted to the right. Vector is
 * automatically grown if necessary.
 *
 * @warning vector must be initialized before calling this function.
 * @warning item must NOT point inside vector->data.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param index Insertion index, in range [0, vector->len].
 * @param item Item to insert (borrowed, not modified).
 * @return true on success, false on invalid index or allocation failure.
 */
bool			vector_insert(t_vector *vector, size_t index, const void *item);

/**
 * @ingroup vector
 * @brief Removes one item at a specific index.
 *
 * Items after index are shifted left to fill the gap. If dst is not NULL, the
 * removed item is copied there before removal.
 *
 * @warning vector must be initialized before calling this function.
 *
 * @param vector Pointer to an initialized vector (borrowed).
 * @param index Index of the item to remove.
 * @param dst Optional destination buffer receiving the removed item (borrowed,
 *            can be NULL).
 * @return true on success, false if index is out of bounds.
 */
bool			vector_remove(t_vector *vector, size_t index, void *dst);

/**
 * @ingroup vector
 * @brief Inserts all items from src into dst at a specific index.
 *
 * Items are copied byte-for-byte from src into dst. Source and destination
 * storages remain independent after the merge.
 *
 * @warning dst and src must be initialized before calling this function.
 * @warning dst and src must be different.
 * @warning dst and src must use the same item_size.
 *
 * @param dst Destination vector receiving the inserted items (borrowed).
 * @param src Source vector providing items to copy (borrowed).
 * @param index Insertion index in dst, in range [0, dst->len].
 * @return true on success, false on invalid input, overflow, or allocation
 *         failure.
 */
bool			vector_merge(t_vector *dst, t_vector *src, size_t index);

#endif
