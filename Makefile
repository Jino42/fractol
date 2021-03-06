# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/02 18:45:43 by ntoniolo          #+#    #+#              #
#    Updated: 2017/07/18 05:07:02 by ntoniolo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

DIR_LFT = libft/
DIR_MLXJI = libmlxji/
DIR_MLX = minilibx_macos/
#DIR_MLX = minilibxcaptain/
DIR_LIB = all_lib/

FLAGS = -Wall -Werror -Wextra -g -I ./include/

FRAMEWORK = -lncurses -framework OpenGL -framework AppKit -framework Opencl

SRC = main.c \
		 init_mlx.c \
		 draw.c \
		 loop.c \
		 flag_arg.c \
		 zoom.c \
		 zoom_complexe.c \
		 draw_tri.c \
		 draw_tree.c \
		 init_fractal.c \
		 end_of_program.c \
		 event/event_key_off.c \
		 event/event_key_on.c \
		 event/event_mouse.c \
		 event/event_move_mouse.c \
		 ncurses/ncurses_init.c \
		 ncurses/ncurses_refresh.c \
		 ncurses/ncurses_menu.c \
		 ncurses/ncurses_menu_bud.c \
		 ncurses/ncurses_parsing.c \
		 ncurses/ncurses_print_parsing_buddhabrot.c \
		 ncurses/ncurses_print_stat.c \
		 ncurses/ncurses_key.c \
		 buddhabrot/buddhabrot_color.c \
		 buddhabrot/over_sampling_resize_buddha.c \
		 cl/cl_draw.c \
		 cl/cl_set_env.c \
		 cl/cl_check_err.c \
		 cl/cl_end_opencl.c \
		 cl/cl_init_opencl.c

SRC_DIR = srcs/

CC = gcc 

MODE = 

INC = includes/

INC_FILES = includes/fractol.h \
			includes/mlx.h

OBJET = $(SRC:.c=.o)

OBJ_DIR = objs/

.PHONY: all, clean, fclean, re, $(NAME), lft, start, end


all: $(OBJ_DIR) lib $(NAME)

$(NAME): $(addprefix $(OBJ_DIR), $(OBJET)) $(INC_FILES)
	@$(CC) $(MODE) -I$(INC) $(addprefix $(OBJ_DIR), $(OBJET)) -L./$(DIR_LIB) -lft -lmlx -lmlxji  $(FRAMEWORK) -o $(NAME)
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"
	@echo "$(MODE)"

$(OBJ_DIR) :
	@mkdir $(DIR_LIB)
	@mkdir $(OBJ_DIR)
	@mkdir $(OBJ_DIR)/cl
	@mkdir $(OBJ_DIR)/event
	@mkdir $(OBJ_DIR)/buddhabrot
	@mkdir $(OBJ_DIR)/ncurses

start:
	@echo "\033[4m\033[33mCreation de $(NAME)   ...\033[0m"

end:
	@echo "\033[4m\033[1m\033[32m>$(NAME) done.\033[0m"

$(OBJ_DIR)%.o: $(addprefix $(SRC_DIR), %.c) $(INC_FILES)
	@echo "\033[34m$^ \033[0m-> \033[1m\033[37m$@\033[0m"
	@($(CC) $(MODE) $(FLAGS)  -I./$(INC) -c -o $@ $<)

lib:
	@(cd $(DIR_LFT) && $(MAKE))
	@(cd $(DIR_MLXJI) && $(MAKE))
	@(cd $(DIR_MLX) && $(MAKE))
	@(cp $(DIR_MLXJI)libmlxji.a ./all_lib/)
	@(cp $(DIR_LFT)libft.a ./all_lib/)
	@(cp $(DIR_MLX)libmlx.a ./all_lib/)

clean:
	@/bin/rm -rf $(OBJ_DIR)
	@(cd $(DIR_LFT) && make clean)
	@(cd $(DIR_MLXJI) && make clean)
	@(cd $(DIR_MLX) && make clean)

fclean: clean
	@/bin/rm -f $(NAME)
	@(rm -rf $(DIR_LIB))
	@(cd $(DIR_LFT) && make fclean)
	@(cd $(DIR_MLXJI) && make fclean)

re: fclean all
