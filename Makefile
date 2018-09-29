NAME = ft_ls

CC = gcc
FLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -I $(LIB_INC_DIR)

INC_DIR = Includes/
INC_NAME = display_files.h display_file_type.h
INC = $(addprefix $(INC_DIR), $(INC_NAME))

SRC_DIR = Sources/
SRC_NAME = main.c display_files.c display_file_type.c

OBJ_DIR = Objects/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))

LIB_DIR = Library/
LIB_INC_DIR = $(LIB_DIR)/Includes/

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_DIR)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -o $@ -c $< 

clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
