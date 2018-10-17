NAME = liblogic.a

FLAGS = -Wall -Werror -Wextra -I $(INC_DIR) -I $(LIBFT_INC_DIR)

INC_DIR = Includes/
INC_NAME = liblogic.h
INC = $(addprefix $(INC_DIR), $(INC_NAME))

SRC_DIR = Sources/
SRC_NAME =  parse_files.c parse_flags.c\
			display_file_info.c define_file_type.c\
			manipulate_file_list.c display_file_list.c\
			sort_file_list.c init_flag_funcs.c prepare_files.c\
			define_chmod.c write_to_display_buff.c

OBJ_DIR = Objects/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))

LIBFT_DIR = ../Libft/
LIBFT_INC_DIR = $(LIBFT_DIR)/Includes/

all: | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	$(CC) $(FLAGS) -o $@ -c $< 

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
