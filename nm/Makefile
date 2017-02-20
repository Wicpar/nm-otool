# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/30 19:43:25 by fnieto            #+#    #+#              #
#    Updated: 2017/02/19 16:04:04 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_nm

CC=gcc

CCFLAGS= -Wall -Wextra -Werror
DLFLAGS=

RM=rm -f

SRCS=src/



SRC=main.c\

HFILES=nm.h\



OBJS=obj/

OBJ=$(SRC:.c=.o)

OBJECTS=$(addprefix $(OBJS), $(OBJ))

INCL=includes/

HEADERS=$(addprefix $(INCL), $(HFILES))

LIB=

$(NAME): $(OBJECTS) $(HEADERS)
	@$(CC) $(DLFLAGS) -o $@ $(OBJECTS) $(LIB)
	@echo "[.o] >> $(NAME)"

$(OBJS)%.o: $(SRCS)%.c
	mkdir -p $(OBJS)
	$(CC) -I $(INCL) $(CFLAGS) -c $< -o $@
	@echo "$< >> $@"
all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
