# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 14:16:37 by wricky-t          #+#    #+#              #
#    Updated: 2022/08/02 14:12:23 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= libftprintf.a

SRCS	:= srcs/ft_printf.c helper/helper.c helper/conv_helper.c \
			helper/fmt_helper.c helper/print_helper.c printer/print_adr.c \
			printer/print_char.c printer/print_hex.c printer/print_num.c \
			printer/print_str.c printer/print_unsigned.c

OBJS	:= $(SRCS:.c=.o)

cc		:= cc

AR		:= ar rcs

CFLAGS	?= -Wall -Werror -Wextra

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	@make all -C libft
	@cp libft/libft.a ./$(NAME)
	@${AR} $(NAME) $(OBJS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@rm -rf libft/*.o

fclean: clean
	@rm -rf libft/libft.a
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re

# styling
GR 	:= \033[1;92m
YL	:= \033[1;93m
DF	:= \033[0m
