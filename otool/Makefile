# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/30 19:43:25 by fnieto            #+#    #+#              #
#    Updated: 2017/02/19 15:48:59 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_otool

CC=gcc

CCFLAGS= -Wall -Wextra -Werror
DLFLAGS=

RM=rm -f

SRCS=src/

SRC=

OBJS=obj/

OBJ=$(SRC:.c=.o)

OBJECTS=$(addprefix $(OBJS), $(OBJ))

INCL=includes/

HFILES=

HEADERS=$(addprefix $(INCL), $(HFILES))

LIB=

$(NAME): $(OBJ) $(HEADERS)
	@$(CC) $(DLFLAGS) -o $@ $(OBJ) $(LIB)
	@echo "[.o] >> $(NAME)"

$(OBJS)%.o: $(SRCS)%.c
	$(CC) -I $(INCL) $(CFLAGS) -c $< -o $@
	@echo "$< >> $@"

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean
