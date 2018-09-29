NAME = libft.a

CC = gcc
FLAGS = -Wall -Wextra -Werror -I $(INC_DIR)

INC_DIR = Includes/
INC_NAME = library.h
INC = $(addprefix $(INC_DIR), $(INC_NAME))

SRC_DIR = Sources/
SRC_NAME = ft_strlen.c ft_strnew.c

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_DIR = Objects/
OBJ_NAME = $(SRC_NAME:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_NAME))

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

.PHONY: re all clean fclean
