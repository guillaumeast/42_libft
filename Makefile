NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

SRCS		:= \
	$(wildcard src/buff/*.c) \
	$(wildcard src/buff/format/*.c) \
	$(wildcard src/chr/*.c) \
	$(wildcard src/conv/*.c) \
	$(wildcard src/gnc/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/malloc/*.c) \
	$(wildcard src/math/*.c) \
	$(wildcard src/mem/*.c) \
	$(wildcard src/print/*.c) \
	$(wildcard src/put/*.c) \
	$(wildcard src/str/*.c)
INCLUDES	:= -I. -I./src/buff/format -I./src/gnc

OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

TEST_NAME	:= tests/tester
TEST_SRCS	:= $(wildcard tests/*.c)
TEST_CFLAGS	:= $(INCLUDES) -g3 -lfut

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

test: re
	$(CC) $(TEST_CFLAGS) $(NAME) $(TEST_SRCS) -o $(TEST_NAME)
	$(TEST_NAME)

doc:
	doxygen docs/Doxyfile

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_NAME).dSYM

fclean: clean
	rm -f $(NAME)
	rm -f $(TEST_NAME)

re: fclean all

.PHONY: all test doc clean fclean re
