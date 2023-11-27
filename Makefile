

NAME = fdf

CC = gcc

INCLUDE_DIR = ./include

LIBFT_DIR = ./libft
LIBFT := $(LIBFT_DIR)/libft.a 
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
GNL_INCLUDE_DIR := $(LIBFT_DIR)/get_next_line

MLX_DIR = ./MLX42
MLX_PATH := $(MLX_DIR)/build/libmlx42.a
MLX_INCLUDE_DIR := $(MLX_DIR)/include/

SRC_DIR = ./src

SRC_FILES = utils.c main.c map_parser.c

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -Wall -Wextra -Werror -g

MLX_FLAGS = -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"

LIBFT_FLAGS := -L$(LIBFT_DIR) -lft

#################################################################

	
##### FDF RECIPES #####

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(GCC_FLAGS) $(OBJS) -o $(NAME)  $(LIBFT_FLAGS)
#$(MLX_PATH) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(GCC_FLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE_DIR) -I$(GNL_INCLUDE_DIR) -c $< -o $@

#-I$(MLX_INCLUDE_DIR) 

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


##### LIBRARY RECIPES #####

libraries:  $(LIBFT) 

#$(MLX_PATH)

#$(MLX_PATH):
#	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4 

$(LIBFT):
	make -C $(LIBFT_DIR)

libmlx_clean:
	make -C $(MLX_DIR)/build clean

libft_clean:
	make -C $(LIBFT_DIR) clean

libft_fclean: libft_clean
	make -C $(LIBFT_DIR) fclean


##### RECIPES FOR ALL #####

fclean_all: fclean libft_fclean libmlx_clean

complete: libraries all

.PHONY: all clean fclean re libmlx libmlx_clean libft

