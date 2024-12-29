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
CC = cc
LIB = ar rcs
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
HEADER = include/pipex.h
#HEADER_BONUS = include/pipex_bonus.h
SRCS = src/pipex.c
OBJS = $(SRCS:.c=.o)
#SRCS_BONUS = src_bonus/pipex_bonus.c
#OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	cp libft/libft.a libft.a
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft.a

src/%.o: src/%.c $(HEADER)
	$(CC) $(CFLAGS) -Iinclude -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS) libft.a
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
