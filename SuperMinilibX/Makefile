# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/26 11:35:35 by bvaujour          #+#    #+#              #
#    Updated: 2024/07/11 17:05:38 by bvaujour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		=	SuperMinilibX.a

SRC			=	ft_power_on.c ft_get_pixel_img.c ft_set_image_pixel.c ft_draw_mirror_to_img.c ft_draw_img_to_img_scaled.c ft_draw_img_to_img.c  ft_init_img_clean.c ft_new_img_xpm_scaled.c ft_new_img_xpm.c 

MLX_PATH	=	./mlx_linux/

MLX_FILE	=	libmlx_Linux.a

MLX_LIB		=	$(addprefix $(MLX_PATH), $(MLX_FILE))

OBJ = $(SRC:.c=.o)


FLAG = -Wall -Werror -Wextra

all : $(NAME)

%.o: %.c
	@cc $(FLAG) -c $< -o $@
	@printf "Compiling SuperMinilibx files.....%-50s \r" $@

$(NAME) : $(MLX_LIB) $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(MLX_LIB):
	@git clone https://github.com/42Paris/minilibx-linux.git mlx_linux
	@make -sC $(MLX_PATH)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME) $(MLX_PATH)

re: fclean all


.PHONY: all clean fclean re