/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvaujour <bvaujour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:34:06 by vanitas           #+#    #+#             */
/*   Updated: 2024/07/18 00:41:22 by bvaujour         ###   ########.fr       */
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
#include <sys/time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
typedef enum	e_state
{
	IDLE,
	RUN,
	FALL,
	DEAD
}				e_state;

typedef enum	e_case
{
	WATER,
	AIR,
	TILE,
	CHARACTER,
	EXIT,
	OUT
}				e_case;

typedef struct	s_control
{
	bool		left;
	bool		right;
}				t_control;

typedef struct	s_coor
{
	int	x;
	int	y;
}				t_coor;

typedef struct	s_locomotion
{
	t_coor		pos;
	float		ms;
	int			dir;
	float		velocity_y;
	float		gravity_scale;
	float		bounce;
	e_state		state;
	t_coor		root;
	int			double_jump;
	int			max_double_jump;
}				t_locomotion;


typedef struct s_flipbook
{
	t_img		*img;
	int			img_per_sec;
	int			nb_img;
}				t_flipbook;

typedef struct	s_draw
{
	char		*name;
	bool		rendered_last_frame;
	t_flipbook	*active_flipbook;
	t_img		*frame;
	t_coor		pos;
	t_img		*last_frame;
	t_coor		last_pos;
	bool		need_redraw;
	int			counter;
	int			dir;
}				t_draw;

typedef	struct	s_bullet
{
	t_locomotion	locomotion;
	t_draw			draw;
	int				dmg;
	int				range;
	bool			active;
	time_t			last_render;
}				t_bullet;

typedef	struct	s_effect
{
	t_draw			draw;
	int				repeat;
	bool			active;
}				t_effect;

typedef struct	s_weapon
{
	t_flipbook		*bullet_flipbook;
	t_flipbook		*muzzle_flipbook;
	t_locomotion	bullet_locomotion;;
	int				bullet_dmg;
	int				att_sec;
	int				bullet_range;
	time_t			last_attack;
	char			*name;
	
}				t_weapon;


typedef struct	s_sprite
{
	bool			end;
	int				dmg;
	bool			active;
	t_locomotion	locomotion;
	t_draw			draw;
}				t_sprite;


typedef struct	s_character
{
	t_flipbook		*idle;
	t_flipbook		*run;
	// t_flipbook		*death;
	t_flipbook		*shoot;
	t_flipbook		*jump;
	t_flipbook		*runshoot;
	t_draw			draw;
	float			speed_scale;
	t_locomotion	locomotion;

	bool			is_attacking;
	bool			is_sprinting;
	t_weapon		weapon;
}				t_character;

typedef struct	s_animate_tile
{
	bool	end;
	t_draw	draw;
	t_img	*fix_part;
	t_coor	pos;
}				t_animate_tile;

typedef struct	s_world
{
	t_animate_tile	*animated_tiles;
	int				tile_w;
	int				tile_h;
	t_coor			camera;
	int				map_width;
	int				map_height;
	int				screen_width;
	int				screen_height;
	char			**map;
	int				line_count;
	int				line_len;
}				t_world;


typedef	struct	s_image_database
{
	t_flipbook		hero_idle;
	t_flipbook		hero_run;
	t_flipbook		hero_jump;
	// t_flipbook		hero_death;
	t_flipbook		hero_shoot;
	t_flipbook		hero_runshoot;
	t_flipbook		fire_bullet;
	t_flipbook		fire_muzzle;
	t_img			contour;
	t_flipbook		waves;
	t_img			waves_fix;
	t_img			door;
	t_img			tile_HautG;
	t_img			tile_HautD;
	t_img			tile_Haut;
	t_img			tile_Milieu;
	t_img			tile_Bas;
	t_img			background;
	t_img			saved_background;

}				t_image_database;

typedef struct	s_paths
{
	char 	*path;
	char 	*next_path;
	char	*tile_hg;
	char	*tile_h;
	char	*tile_hd;
	char	*tile_m;
	char	*tile_b;
	char	*door;
	char	*background;
	char	*sky;
	char	*ground;
}				t_paths;

typedef struct	s_data
{
	t_mlx				engine;
	t_character			hero;
	t_image_database	img_db;
	t_world				world;
	t_control			controls;
	t_bullet			bullets[200];
	t_effect			muzzles[200];
	t_draw				*to_draw[200];
	t_draw				*to_erase[200];
	int					stock;
	int					nb_to_draw;
	int					nb_to_erase;
	int					fps;
	t_paths				paths;
}				t_data;


e_case		collision(t_world *world, t_coor pos);
void		init(t_data *data);
void		init_values(t_data *data);

void		render(t_data *data);
void		new_empty_img(t_data *data, t_img *image, int width, int height);
void		quit(t_data *data);
int			key_release(int keypress, t_data *data);
int			key_press(int keypress, t_data *data);
int			button_press(int button, int x, int y, t_data *data);
int			button_release(int button, int x, int y, t_data *data);
void		map_handle(t_data *data);
time_t		gettime();
void		show_fps();
void		move_camera_x(t_data *data, int distance);
void		set_pos_y(t_locomotion *locomotion, t_draw *draw, int new_pos_y);
void		set_pos_x(t_locomotion *locomotion, t_draw *draw, int new_pos_x);
void		add_position(t_locomotion *locomotion, t_draw *draw, int delta_x, int delta_y);
void		update(t_data *data);
void		init_values(t_data *data);
void 		character_move(t_character *character, t_world *world, int distance);
void		character_change_state(t_character *character, e_state new_state);
void		character_fire(t_character *character, t_bullet *bullets, t_effect *muzzles);
void		character_sprint(t_character *character, float acceleration);
void		init_draw(t_draw *draw, t_flipbook *flipbook, t_coor pos, char *name);
void		add_to_draw_list(t_data *data, t_draw *draw);
void		add_to_erase_list(t_data *data, t_draw *draw);
bool		is_in_screen(t_world *world, t_img *img, t_coor pos);
void		free_reusable_data(t_data *data);
void		quit_error(t_data *data, const char *str);
int			secure_open(t_data *data, char *path);
void		secure_close(t_data *data, int fd);
t_img		ft_new_img(t_data *data, char *path);
















#endif
