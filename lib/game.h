/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:34:06 by vanitas           #+#    #+#             */
/*   Updated: 2024/03/26 18:34:17 by bvaujour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../libft/libft.h"
# include "../SuperMinilibX/SuperMinilibX.h"
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <fcntl.h>
# include <math.h>
# include <X11/Xlib.h>
# include <stdbool.h>

typedef struct s_info
{
	int		pos_x;
	int		pos_y;
	bool	is_jumping;
	int     velocity_y;
}				t_info;
typedef struct s_data
{
	t_mlx		engine;
	t_img		hero;
	t_info		hero_info;
}				t_data;

#endif
