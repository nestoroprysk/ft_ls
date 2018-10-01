NAME = ft_ls

CC = gcc
FLAGS = -Wall -Wextra -Werror -I $(LIB_LOGIC_INC_DIR)

LIB_LOGIC_DIR = Liblogic/
LIB_LOGIC_INC_DIR = $(LIB_LOGIC_DIR)/Includes/

LIB_FT_DIR = Libft/

SRC_NAME = main.c

DEPS =  $(LIB_LOGIC_DIR)/Sources/*.c $(LIB_LOGIC_INC_DIR)/*.h\
		$(LIB_FT_DIR)/Sources/*.c $(LIB_FT_DIR)/Includes/*.h

all: $(NAME)

$(NAME): $(SRC_NAME) $(DEPS)
	make -C $(LIB_FT_DIR)
	make -C $(LIB_LOGIC_DIR)
	$(CC) -o $(NAME) $(SRC_NAME) $(FLAGS) -L $(LIB_LOGIC_DIR) -llogic -L $(LIB_FT_DIR) -lft

clean:
	make clean -C $(LIB_FT_DIR)
	make clean -C $(LIB_LOGIC_DIR)

fclean: clean
	make fclean -C $(LIB_FT_DIR)
	make fclean -C $(LIB_LOGIC_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: re all clean fclean
