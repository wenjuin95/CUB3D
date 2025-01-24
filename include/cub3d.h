/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:10 by welow             #+#    #+#             */
/*   Updated: 2025/01/24 15:38:42 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>
# include "parse.h"

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363
# define MAP 109

# define PI 3.142

//campus
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1

//mouse sensitivity
# define MOUSE_ROTATE 0.025

//campus
# define WIN_WIDTH 1280
# define WIN_HEIGHT 1024

////full screen
//# define WIN_WIDTH 1920
//# define WIN_HEIGHT 1200

////full screen
//# define MOVE_SPEED 0.9
//# define ROTATE_SPEED 0.1

////laptop
//# define WIN_WIDTH 640
//# define WIN_HEIGHT 480

////laptop
//# define MOVE_SPEED 0.1
//# define ROTATE_SPEED 0.1

# define TEXTURE_SIZE 64
# define VERTICAL 0
# define HORIZONTAL 1

# define MINIMAP_SIZE 20
# define MINIMAP_PLAYER 0x00FF00 // Green
# define MINIMAP_WALL 0x000000 // black
# define MINIMAP_FLOOR 0xE6E6E6 // Light Gray

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	char		*map_add;
	int			on_map;
	int			mouse;
	t_map		map;
	t_minimap	minimap;
	t_player	player;
	t_raycast	ray;
	t_img		img;
	t_tex		texture;
}	t_data;

//debug.c
void	debuger(t_data *data);
void	debug_data(t_data *data);
void	debug_minimap(t_data *data);
void	debug_image(t_img *img);
void	debug_texture(t_tex *texture);
void	debug_raycast(t_raycast *ray);
void	debug_player(t_player *player);
void	debug_parsing(t_data *data);

//initialize.c
void	initialize_data(t_data *data);
int		initialize_mlx(t_data *data);
void	initialize_mlx_hook(t_data *data);
void	initialize_image(t_data *data, t_img *img, int w_width, int w_height);

//initialize_texture1.c
void	initialize_texture(t_data *data);

// exit.c
int		close_win(t_data *data);
void	free_array(void **array);
void	clean_data(t_data *data);
int		clean_and_exit(t_data *data);

// render_image.c
void	color_pixel_put(t_img *img, int x, int y, int color);
void	put_image(t_data *data);
void	init_map_size_for_texture(t_data *data);
void	render_the_image(t_data *data);

////render_minimap.c
void	draw_square(t_data *data, int x, int y, int color);
void	render_minimap(t_data *data);
int	put_minimap(t_data *data);

//raycast_and_dda.c
void	initialize_ray(int x, t_raycast *ray, t_player *player);
void	get_step(t_raycast *ray, t_player *player);
void	perform_dda(t_data *data, t_raycast *ray);
int		raycasting(t_player *player, t_data *data);

//draw.c
void	get_texture_index(t_data *data, t_raycast *ray);
void	define_line_height(t_raycast *ray, t_data *data);
void	define_texture(t_raycast *ray, t_data *data, t_player *player);
void	update_texture_pixel(t_data *data, t_tex *tex, t_raycast *ray, int x);

//parsing.c
//int		parsing(t_data *data, char **file_name);

//control.c
int		handle_key_press(int keycode, t_data *data);
int		handle_key_release(int keycode, t_data *data);

//check_movement.c
int		check_move(t_data *data, double move_x, double move_y);
int		rotate_left(t_data *data);
int		rotate_right(t_data *data);
int		update_image(t_data *data);

//movement.c
int		move_forward(t_data *data);
int		move_backward(t_data *data);
int		move_left(t_data *data);
int		move_right(t_data *data);
int		player_movement(t_data *data);

//handle_mouse.c
int		handle_mouse(int x, int y, t_data *data);

//parse/utils2.c
void	check_player_position(t_data *data);
void	init_player_dir(t_data *data);

void	ft_error(char *str);
size_t	ft_len(char *s);

int	put_minimap(t_data *data);

#endif
