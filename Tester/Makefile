NAME = tests

CC = clang++
FLAGS = -std=c++17 -Wall -Wextra -Werror -I $(LIB_LOGIC_INC_DIR)

LIB_LOGIC_DIR = ../Liblogic/
LIB_LOGIC_INC_DIR = $(LIB_LOGIC_DIR)/Includes/

LIB_FT_DIR = ../Libft/

SRC_NAME = valid_flags.cpp invalid_flags.cpp strange_flags.cpp

DEPS =  $(LIB_LOGIC_DIR)/Sources/*.c $(LIB_LOGIC_INC_DIR)/*.h\
		$(LIB_FT_DIR)/Sources/*.c $(LIB_FT_DIR)/Includes/*.h

CATCH_HEADER = catch.hpp

CATCH_LINK = 'https://github.com/catchorg/Catch2/releases/download/v2.4.1/catch.hpp'

all: | $(CATCH_HEADER)

$(CATCH_HEADER):
	curl -o $(CATCH_HEADER) -L $(CATCH_LINK)

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
	rm -f $(CATCH_HEADER)

re: fclean all

.PHONY: re all clean fclean
