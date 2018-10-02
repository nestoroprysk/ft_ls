NAME = liblogic.a

FLAGS = -Wall -Werror -Wextra -I $(INC_DIR) -I $(LIBFT_INC_DIR)

INC_DIR = Includes/
INC_NAME = liblogic.h
INC = $(addprefix $(INC_DIR), $(INC_NAME))

SRC_DIR = Sources/
SRC_NAME =  parse_files_to_display.c parse_flags.c\
			display_file_info.c define_file_type.c\
			manipulate_file_list.c

OBJ_DIR = Objects/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))

LIBFT_DIR = ../Libft/
LIBFT_INC_DIR = $(LIBFT_DIR)/Includes/

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -o $@ -c $< 

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
