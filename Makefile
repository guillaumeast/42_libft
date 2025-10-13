# TODO: add 'bonus' rule to compile bonus functions (DON'T COMPILE THEM WITH 'all' rule!)
# TODO: add main.c for memory leaks check (can't memcheck with Criterion activated)

NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3

SRC			= $(wildcard *.c)
OBJ_DIR		= obj
OBJ			= $(SRC:%.c=$(OBJ_DIR)/%.o)

# Criterion flags (portable: use pkg-config if available)
CRIT_CFLAGS := $(shell pkg-config --cflags criterion 2>/dev/null)
CRIT_LIBS   := $(shell pkg-config --libs   criterion 2>/dev/null)
ifeq ($(CRIT_LIBS),)
CRIT_LIBS := -lcriterion
endif
TEST_DIR	= tests
TEST_SRCS	= $(wildcard $(TEST_DIR)/*.c)
TEST_BIN 	= $(TEST_DIR)/run_tests

# OS detection for choosing memory leaks check command
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
LEAKS_CMD = leaks --atExit -- ./$(TEST_BIN) --verbose
else
LEAKS_CMD = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TEST_BIN) --verbose
endif

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile unit tests (with criterion)
test_bin: $(NAME) $(TEST_SRCS)
	$(CC) $(CFLAGS) -I. -I$(TEST_DIR) $(CRIT_CFLAGS) -o $(TEST_BIN) $(TEST_SRCS) $(NAME) $(CRIT_LIBS)

# Run unit tests (with criterion)
test: test_bin
	./$(TEST_BIN)

# Run memory leaks check
leaks: test_bin
	$(LEAKS_CMD)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(TEST_BIN)

re: fclean all

.PHONY: all test_bin test leaks clean fclean re