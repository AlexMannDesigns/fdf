

NAME = fdf

CC = gcc

INCLUDE_DIR = ./include

MLX_PATH = MLX42/build/libmlx42.a
MLX_INCLUDE_DIR = ./MLX42/include/

SRC_DIR = ./src

SRC_FILES = example.c

SRCS := $(patsubst %, $(SRC_DIR)/%, $(SRC_FILES))

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"

$(NAME): $(MLX_PATH) $(OBJS)
	$(CC)  $(OBJS) -o $(NAME) $(MLX_PATH) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC)  -I$(INCLUDE_DIR) -I$(MLX_INCLUDE_DIR) -c $< -o $@

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all



