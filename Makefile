

NAME = fdf

CC = gcc

INCLUDE_DIR = ./include

LIBFT_DIR = ./libft
LIBFT := $(LIBFT_DIR)/libft.a 
LIBFT_INCLUDE_DIR := $(LIBFT_DIR)/include
GNL_INCLUDE_DIR := $(LIBFT_DIR)/get_next_line

MLX_DIR = ./MLX42
MLX := $(MLX_DIR)/build/libmlx42.a
MLX_INCLUDE_DIR := $(MLX_DIR)/include/

SRC_DIR = ./src

SRC_FILES = projection_control.c draw_wireframe.c fdf_control.c plot_line.c key_events.c utils.c main.c map_parser.c

OBJ_DIR = ./obj
OBJS := $(patsubst %, $(OBJ_DIR)/%, $(SRC_FILES:.c=.o))

GCC_FLAGS = -Wall -Wextra -Werror -g

#MLX_FLAGS = -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -lglfw -L"$(MLX_DIR)/build" -lmlx42
#if on hive imac:
MLX_FLAGS = -L"/Users/$(USER)/.brew/opt/glfw/lib/" -lglfw -L"$(MLX_DIR)/build" -lmlx42


LIBFT_FLAGS := -L"$(LIBFT_DIR)" -lft

INCLUDE_FLAGS := -I$(INCLUDE_DIR) -I$(LIBFT_INCLUDE_DIR) -I$(GNL_INCLUDE_DIR) -I$(MLX_INCLUDE_DIR)

#################################################################

	
##### FDF RECIPES #####

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(GCC_FLAGS) $(OBJS) -o $(NAME) $(LIBFT_FLAGS) $(MLX_FLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(GCC_FLAGS) $(INCLUDE_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


##### LIBRARY RECIPES #####

libraries:  $(LIBFT) $(MLX)

$(MLX):
	cmake -DDEBUG=1 $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4 

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

.PHONY: all clean fclean re libmlx libmlx_clean libft

