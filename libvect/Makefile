# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguiller <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/07 11:15:29 by lguiller          #+#    #+#              #
#    Updated: 2018/07/26 16:01:07 by lguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##  VARIABLES   ##
##################

NAME	= libvect.a
SRC		= rotation_3d.c
OBJ		= $(SRC:.c=.o)
FLAGS	= -Wall -Wextra -Werror

##################
##    COLORS    ##
##################

_GREY		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_PURPLE		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_BOLD		= "\033[1m"
_CLEAR		= "\033[2K"
_SAVE		= "\033[7"
_BACK		= "\033[8"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"

##################
##   TARGETS    ##
##################

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	@echo $(_GREEN)"Done."$(_END)$(_SHOW_CURS)

%.o: %.c
	@gcc $(FLAGS) -c $^ -o $@

clean:
	@/bin/rm -f $(OBJ)

fclean: clean
	@/bin/rm -f $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE)
