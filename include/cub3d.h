/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:56:10 by welow             #+#    #+#             */
/*   Updated: 2024/12/02 14:41:02 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "struct.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <X11/X.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define LEFT 65361
# define RIGHT 65363

////laptop
//# define MOVE_SPEED 0.011
//# define ROTATE_SPEED 0.03

//campus
# define MOVE_SPEED 0.1
# define ROTATE_SPEED 0.1

//campus
# define WIN_WIDTH 1280
# define WIN_HEIGHT 1024

////laptop
//# define WIN_WIDTH 640
//# define WIN_HEIGHT 480

# define TEXTURE_SIZE 64

# define MAP_PIXEL 128
# define MAP_VIEW 4

# define VERTICAL_WALL 0
# define HORIZONTAL_WALL 1

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	char		**map;
	int			map_width;
	int			map_height;
	int			**tex_pixel;
	int			**tex_data;
	t_player	player;
	t_raycast	ray;
	t_img		img;
	t_tex		texture;
}	t_data;

void	debuger(t_data *data);
void	debug_parsing(t_data *data);

//initialize_image.c
//static void	get_xpm_data(t_data *data, char *path)
//static int	*init_texture_data(t_data *data, char *path)
void	initialize_texture(t_data *data);

// exit.c
int		close_win(t_data *data);
void	free_array(void **array);
void	clean_mlx(t_data *data);
void	clean_data(t_data *data);
int	clean_and_exit(t_data *data);
int	close_win(t_data *data);

// render_image.c
//static void	set_image_pixel(t_img *img, int x, int y, int color)
//static void	set_image(t_data *data, t_img *img, int x, int y)
void	put_image(t_data *data);
void	initialize_image(t_data *data, t_img *img, int w_width, int w_height);
void	init_map_size_for_texture(t_data *data);
void	render_the_image(t_data *data);

//raycast_and_dda.c
void	calculate_ray_and_grid(int x, t_raycast *ray, t_player *player);
void	set_dda(t_raycast *ray, t_player *player);
void	perform_dda(t_data *data, t_raycast *ray);
void	calculate_line_height_to_draw(t_raycast *ray, t_data *data, t_player *player);
void	get_texture_index(t_data *data, t_raycast *ray);
void	update_texture_pixel(t_data *data, t_tex *tex, t_raycast *ray, int x);
int	raycasting(t_player *player, t_data *data);

//parsing.c
int parsing(t_data *data, char **file_name);

//control.c
int	handle_key_press(int keycode, t_data *data);
int	handle_key_release(int keycode, t_data *data);

//check_movement.c
int	check_move(t_data *data, double move_x, double move_y);
int	rotate_left(t_data *data);
int	rotate_right(t_data *data);
int	update_image(t_data *data);

//movement.c
int	move_forward(t_data *data);
int	move_backward(t_data *data);
int	move_left(t_data *data);
int	move_right(t_data *data);
int	player_movement(t_data *data);

#endif
