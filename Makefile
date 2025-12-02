NAME		= libft.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

# Mandatory part
SRCS		:= $(filter-out ft_lst%.c, $(wildcard *.c))
OBJ_DIR		:= obj
OBJ			:= $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Bonus part
BONUS_SRCS	:= $(wildcard ft_lst*.c)
BONUS_OBJ	:= $(BONUS_SRCS:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(NAME) $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
