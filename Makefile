# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lguiller <lguiller@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/16 12:18:12 by lguiller          #+#    #+#              #
#    Updated: 2018/09/04 17:22:07 by lguiller         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##################
##  VARIABLES   ##
##################

OPE_SYS			= $(shell uname)
NAME			= rtv1
SRCS1			= main.c parse_csv.c ray_tracing.c mouse.c display.c \
				equations.c shadow.c init.c
SRCS			= $(addprefix $(SRCS_DIR), $(SRCS1))
OBJS			= $(addprefix $(OBJS_DIR), $(SRCS1:.c=.o))
SRCS_DIR		= srcs/
OBJS_DIR		= objs/
LIBFT			= libft/libft.a
LIBVECT			= libvect/libvect.a
MINILIBX		= $(MLX_DIR)/libmlx.a
FLAGS			= -Wall -Wextra -Werror -O2 -g

ifeq ($(OPE_SYS), Linux)
	MLX_DIR		= minilibx_x11
	INCLUDES	= -I includes -I libft -I libvect -I $(MLX_DIR) -I /usr/include
	FRAMEWORK	= -L$(MLX_DIR) -lmlx -L/usr/lib -lXext -lX11 -lm
else
	MLX_DIR		= minilibx
	INCLUDES	= -I includes -I libft -I libvect -I $(MLX_DIR)
	FRAMEWORK	= -framework OpenGL -framework Appkit
endif

##################
##    COLORS    ##
##################

_BLACK		= "\033[30m"
_RED		= "\033[31m"
_GREEN		= "\033[32m"
_YELLOW		= "\033[33m"
_BLUE		= "\033[34m"
_VIOLET		= "\033[35m"
_CYAN		= "\033[36m"
_WHITE		= "\033[37m"
_END		= "\033[0m"
_CLEAR		= "\033[2K"
_HIDE_CURS	= "\033[?25l"
_SHOW_CURS	= "\033[?25h"
_UP			= "\033[A"
_CUT		= "\033[k"

##################
##   TARGETS    ##
##################

.PHONY: all title libft minilibx libvect create_dir clean fclean re

all: $(NAME)

create_dir:
	@./.check_dir.sh $(OBJS_DIR)

libft: title
	@make -sC libft

libvect: libft
	@make -sC libvect

minilibx: libvect
	@make -sC $(MLX_DIR) 2>/dev/null

$(NAME): minilibx create_dir $(OBJS)
	@gcc $(FLAGS) $(OBJS) $(LIBFT) $(LIBVECT) $(FRAMEWORK) $(MINILIBX) -o $(NAME)
	@echo $(_CLEAR)$(_YELLOW)"building - "$(_GREEN)$(NAME)$(_END)
	@echo $(_GREEN)"Done."$(_END)$(_SHOW_CURS)


$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@gcc $(FLAGS) $(INCLUDES) -c $^ -o $@

clean:
	@make -sC libft clean
	@make -sC libvect clean
	@make -sC $(MLX_DIR) clean
	@/bin/rm -f $(OBJS)

fclean: clean
	@make -sC libft fclean
	@make -sC libvect fclean
	@/bin/rm -f $(NAME)

re:
	@$(MAKE) -s fclean
	@$(MAKE) -s

title:
	@echo $(_RED)
	@echo "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"
	@echo
	@echo "                        ::::::::: ::::::::::: :::     :::   :::                "
	@echo "                       :+:    :+:    :+:     :+:     :+: :+:+:                 "
	@echo "                      +:+    +:+    +:+     +:+     +:+   +:+                  "
	@echo "                     +#++:++#:     +#+     +#+     +:+   +#+                   "
	@echo "                    +#+    +#+    +#+      +#+   +#+    +#+                    "
	@echo "                   #+#    #+#    #+#       #+#+#+#     #+#                     "
	@echo "                  ###    ###    ###         ###     #######                    "
	@echo
	@echo "◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆"
	@printf $(_YELLOW)
	@echo "                                                       2018 © lguiller bede-fre"
	@echo $(_END)
