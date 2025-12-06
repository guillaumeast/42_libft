NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

SRCS		:= \
	$(wildcard chr/*.c) \
	$(wildcard conv/*.c) \
	$(wildcard lst/*.c) \
	$(wildcard malloc/*.c) \
	$(wildcard mem/*.c) \
	$(wildcard put/*.c) \
	$(wildcard str/*.c)
INCLUDES	:= -I.

OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
