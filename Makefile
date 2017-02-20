# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fnieto <fnieto@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/30 19:43:25 by fnieto            #+#    #+#              #
#    Updated: 2017/02/19 15:26:08 by fnieto           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM=ft_nm

OTOOL=ft_otool

all: $(NM) $(OTOOL)

$(NM):
	make -C nm/
	cp -f nm/$(NM) .

$(OTOOL):
	make -C otool/
	cp -f otool/$(OTOOL) .

clean:
	make -C nm/ clean
	make -C otool/ clean

fclean:
	make -C nm/ fclean
	make -C otool/ fclean
	rm -f $(OTOOL)
	rm -f $(NM)

re: fclean all

.PHONY: clean fclean
