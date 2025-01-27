# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffierro- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/26 17:42:15 by ffierro-          #+#    #+#              #
#    Updated: 2024/12/26 17:42:16 by ffierro-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
BONUS_MARKER = .marker

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
LIB = ar rcs
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror

HEADER = include/pipex.h
HEADER_BONUS = include/pipex_bonus.h

SRC_DIR = src
SRC_DIR_BONUS = src_bonus
SRCS = $(SRC_DIR)/pipex.c $(SRC_DIR)/split_command.c $(SRC_DIR)/utils.c
SRCS_BONUS = $(SRC_DIR_BONUS)/pipex_bonus.c $(SRC_DIR_BONUS)/utils_bonus.c \
			$(SRC_DIR_BONUS)/childs_bonus.c \
			$(SRC_DIR_BONUS)/utils2_bonus.c \
			$(SRC_DIR_BONUS)/split_command_bonus.c \
			$(SRC_DIR_BONUS)/here_doc_bonus.c \
			$(SRC_DIR_BONUS)/get_next_line_bonus.c

OBJ_DIR = obj
OBJ_DIR_BONUS = obj_bonus
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:$(SRC_DIR_BONUS)/%.c=$(OBJ_DIR_BONUS)/%.o)

RED         = \033[91;1m
GREEN       = \033[92;1m
CLEAR_COLOR = \033[0m

all: $(NAME)

bonus: $(BONUS_MARKER)

$(BONUS_MARKER): $(NAME_BONUS)
	@cp $(NAME_BONUS) $(NAME)
	@touch $(BONUS_MARKER)


$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled! ;)$(CLEAR_COLOR)"

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "$(GREEN)$(NAME_BONUS) compiled! ;)$(CLEAR_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(OBJ_DIR_BONUS)/%.o: $(SRC_DIR_BONUS)/%.c $(HEADER_BONUS)
	@mkdir -p $(OBJ_DIR_BONUS)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

$(LIBFT): 
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft compiled!$(CLEAR_COLOR)"


clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Object files removed!$(CLEAR_COLOR)"

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) $(BONUS_MARKER)
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)All files removed!$(CLEAR_COLOR)"

re: fclean all

.PHONY: all clean fclean re bonus
