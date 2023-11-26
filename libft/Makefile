# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amann <amann@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 11:48:22 by amann             #+#    #+#              #
#    Updated: 2022/09/27 15:46:52 by amann            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INCLUDE_DIR = ./include

LIB_DIR = ./srcs
LIB_FILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c			\
		ft_isdigit.c ft_islower.c ft_lstiter.c ft_memcpy.c ft_memcmp.c			\
		ft_itoa.c ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_isprint.c			\
		ft_lstmap.c ft_lstnew.c	ft_memalloc.c ft_memccpy.c ft_memchr.c			\
		ft_memdel.c ft_memmove.c ft_memset.c ft_putchar.c ft_putchar_fd.c		\
		ft_putendl.c ft_strcat.c ft_strequ.c ft_strmap.c ft_strmapi.c			\
		ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c	\
		ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c	\
		ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlen.c		\
		ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnequ.c ft_strnew.c			\
		ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c			\
		ft_free_array.c ft_iswhitespace.c ft_abs.c ft_strnstr.c ft_strrchr.c	\
		ft_toupper.c ft_abs_long.c ft_lstadd_back.c ft_strndup.c ft_isupper.c	\
		ft_itoa_base.c ft_itoa_base_unsigned.c ft_split_whitespace.c			\
		ft_array_len.c ft_print_array.c ft_is_dir.c ft_is_valid_path.c			\
		ft_string_insert.c ft_remove_from_array.c ft_lst_len.c \
		ft_free_char_array.c

GNL_DIR	:= ./get_next_line
GNL_FILES = get_next_line.c

OBJ_DIR = ./obj
LIB_OBJS := $(patsubst %, $(OBJ_DIR)/%, $(LIB_FILES:.c=.o))  
GNL_OBJ_DIR := $(GNL_DIR)/obj
GNL_OBJS := $(patsubst %, $(GNL_OBJ_DIR)/%, $(GNL_FILES:.c=.o))  

CC = gcc
FLAGS = -Wall -Wextra -Werror -g


##### RULES #####

$(NAME): $(LIB_OBJS) $(GNL_OBJS)
	ar rcs $(NAME) $(LIB_OBJS) $(GNL_OBJS)
	@echo "\n\033[32mlibft.a compiled\033[0m\n"

$(OBJ_DIR)/%.o: $(LIB_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(GNL_DIR) -c $< -o $@

$(GNL_OBJ_DIR)/%.o: $(GNL_DIR)/%.c | $(GNL_OBJ_DIR)
	$(CC) $(FLAGS) -I$(INCLUDE_DIR) -I$(GNL_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(GNL_OBJ_DIR):
	@mkdir -p $(GNL_OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(GNL_OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

all: $(NAME)
