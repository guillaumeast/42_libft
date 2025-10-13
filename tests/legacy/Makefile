NAME	= test
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -I..

SRC		= test.c $(wildcard units/part1/*.c) $(wildcard units/part2/*.c) $(wildcard units/bonus/*.c) $(wildcard utils/*.c)
OBJ_DIR	= obj
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

../libft.a:
	$(MAKE) -C ..

$(NAME): ../libft.a $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) ../libft.a -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re