# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 14:28:02 by vanitas           #+#    #+#              #
#    Updated: 2024/07/14 18:09:37 by bvaujour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME		=	game

NAME_B		=	game_bonus
 
CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror -g

LIBFT_PATH	=	./libft/

LIBFT_FILE	=	libft.a

MLX_FILE	=	SuperMinilibX.a mlx_linux/libmlx_Linux.a

LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

MLX_FLAG	=	-lX11 -lXext

MLX_PATH	=	./SuperMinilibX/

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

MLX_EX		=	$(MLX_LIB) $(MLX_FLAG)

SRC_DIR		=	./src/

SRC_DIR_B	=	./src_bonus/

H_FILES		=	./lib/game.h

H_FILES_B	=	./lib/game_bonus.h

C_FILE		=	main.c						\
				init.c						\
				utils.c						\
				end.c						\
				control.c					\
				map.c						\
				position.c					\
				character_actions.c			\
				updates.c					\
				render.c					\
	
C_FILE_B	=	main.c						\

SRC			=	$(addprefix $(SRC_DIR), $(C_FILE))

SRC_B		=	$(addprefix $(SRC_DIR_B), $(C_FILE_B))

OBJ_DIR		=	./Objects/

OBJ_DIR_B	=	./Objects_bonus/

OBJ			=	$(addprefix $(OBJ_DIR), $(C_FILE:.c=.o))

OBJ_B		=	$(addprefix $(OBJ_DIR_B), $(C_FILE_B:.c=.o))

DEP		=	$(OBJ:.o=.d)
# Colors
GREEN		=	\e[92;1;118m
YELLOW		=	\e[93;1;226m
GRAY		=	\e[33;2;37m	
RESET		=	\e[0m
CURSIVE		=	\e[33;3m


	
all: $(NAME)

$(NAME): $(H_FILES) $(MLX_LIB) $(LIBFT_LIB) $(OBJ) Makefile
	$(CC) $(OBJ) $(LIBFT_LIB) $(MLX_EX) -lm -o $(NAME)
	@printf "$(GREEN)- Mandatory executable ready.\n$(RESET)"


$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(H_FILES)
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@
	@$(CC) $(FLAGS) -MM $< -MF $(OBJ_DIR)$*.d -MT $(OBJ_DIR)$*.o

bonus : $(NAME_B)

$(NAME_B): $(MLX_LIB) $(LIBFT_LIB) $(OBJ_B) $(H_FILES_B) Makefile
	@$(CC) $(OBJ_B) $(LIBFT_LIB) $(MLX_EX) -lm -o $(NAME_B)
	@printf "$(GREEN)- Bonus executable ready.\n$(RESET)"

$(OBJ_DIR_B)%.o: $(SRC_DIR_B)%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@
	@$(CC) $(FLAGS) -MM $< -MF $(OBJ_DIR_B)$*.d -MT $(OBJ_DIR_B)$*.o

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)
$(MLX_LIB):
	@make -C $(MLX_PATH)

push: fclean
	git add *
	git commit -m auto
	git push

clean:
	@make clean -sC $(LIBFT_PATH)
	@make clean -sC $(MLX_PATH)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR_B)
	@printf "$(YELLOW)- Object files removed.$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f $(NAME_B)
	@make fclean -C $(LIBFT_PATH)
	@make fclean -sC $(MLX_PATH)
	@printf "$(YELLOW)- Executable removed.$(RESET)\n"

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re
