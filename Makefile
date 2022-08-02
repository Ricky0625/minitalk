# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 12:30:07 by wricky-t          #+#    #+#              #
#    Updated: 2022/08/02 13:24:17 by wricky-t         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= server client

SRCS	:= server.c client.c

OBJS	:= $(SRCS:.c=.o)

CC		:= cc

CFLAGS	?= -Wall -Werror -Wextra

all: server client
	@echo "  $(RD)╔══╦╦═╦╦╦══╦═╦╗╔╦╗$(DF)"
	@echo "  $(RD)║║║║║║║║╠╗╔╣╩║╚╣═╣$(DF)"
	@echo "  $(RD)╚╩╩╩╩╩═╩╝╚╝╚╩╩═╩╩╝$(DF)"
	@echo "$(GR)===== $(UGR)HOW TO USE$(DF)$(GR) =====$(DF)"
	@echo "$(WH)./server$(DF)"
	@echo "$(WH)./client [pid] [msg]$(DF)"
	@echo "$(GR)======================$(DF)"
	

server: server.o
	@$(CC) $(CFLAGS) $< -o server
	@echo "$(GR)✓ server created$(DF)"

client:	client.o
	@$(CC) $(CFLAGS) $< -o client
	@echo "$(GR)✓ client created$(DF)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(WH)↺ compiling...$(DF)"

clean:
	@rm -rf $(OBJS)
	@echo "$(RD)✗ object files$(DF)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RD)✗ server & client destroyed$(DF)"
	

re: fclean all

.PHONY: clean fclean re

# styling
GR 	:= \033[1;92m
UGR := \033[4;32m
RD	:= \033[1;31m
WH	:= \033[1;37m
DF	:= \033[0m