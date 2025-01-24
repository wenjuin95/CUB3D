/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:38:25 by welow             #+#    #+#             */
/*   Updated: 2025/01/24 13:55:51 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief check the position can be move or not
 * @param data the data
 * @param move_x the x position to move
 * @param move_y the y position to move
 * @return 1 if player move, 0 if player not move
 * @note 1. check if the player chg position the current position will
 * 			replace '0'
*/
int	check_move(t_data *data, double move_x, double move_y)
{
	int	moved;

	moved = 0;
	if (data->map.map[(int)data->player.pos_y][(int)move_x] != '1')
	{
		data->map.map[(int)data->player.pos_y][(int)data->player.pos_x]
			= '0';
		data->map.map[(int)data->player.pos_y][(int)move_x] = 'P';
		data->player.pos_x = move_x;
		moved = 1;
	}
	if (data->map.map[(int)move_y][(int)data->player.pos_x] != '1')
	{
		data->map.map[(int)data->player.pos_y][(int)data->player.pos_x]
			= '0';
		data->map.map[(int)move_y][(int)data->player.pos_x] = 'P';
		data->player.pos_y = move_y;
		moved = 1;
	}
	return (moved);
}

/**
 * @brief rotate the player right
 * @param data the data
 * @return 1 for player rotate right
 * @note 1. dir_x and dir_y calculate using rotation matrix to get x and y
 * @note 2. plane_x and plane_y calculate using rotation matrix to get x and y
*/
int	rotate_right(t_data *data)
{
	double	tmp_dir_x;
	double	tmp_plane_x;
	double	rotate_angle;

	if (data->mouse == 1)
		rotate_angle = MOUSE_ROTATE;
	else
		rotate_angle = ROTATE_SPEED;
	tmp_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rotate_angle)
		- data->player.dir_y * sin(rotate_angle);
	data->player.dir_y = tmp_dir_x * sin(rotate_angle) + data->player.dir_y
		* cos(rotate_angle);
	tmp_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rotate_angle)
		- data->player.plane_y * sin(rotate_angle);
	data->player.plane_y = tmp_plane_x * sin(rotate_angle)
		+ data->player.plane_y * cos(rotate_angle);
	return (1);
}

/**
 * @brief rotate the player left
 * @param data the data
 * @return 1 for player rotate left
 * @note 1. store the dir_x in tmp_x for prevent overwrite
 * 			the value before calculation
 * @note 2. dir_x and dir_y calculate using rotation matrix to get x and y
 * @note 	vector(x, y) is rotated by angle using:
 * 				x' = x * cos(angle) - y * sin(angle)
 * 				y' = x * sin(angle) + y * cos(angle)
 * 			"ROTATE_SPEED" is the angle to rotate (0.1 is the angle of
 * 			1 degree)
 * @note 3. tmp_x store the plane_x to prevent overwrite the
 * 			value before calculation
 * @note 4. plane_x and plane_y calculate also using rotation matrix to get x
 * 			and y
*/
int	rotate_left(t_data *data)
{
	double	tmp_dir_x;
	double	tmp_plane_x;
	double	rotate_angle;

	if (data->mouse == 1)
		rotate_angle = MOUSE_ROTATE;
	else
		rotate_angle = ROTATE_SPEED;
	tmp_dir_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-rotate_angle)
		- data->player.dir_y * sin(-rotate_angle);
	data->player.dir_y = tmp_dir_x * sin(-rotate_angle) + data->player.dir_y
		* cos(-rotate_angle);
	tmp_plane_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-rotate_angle)
		- data->player.plane_y * sin(-rotate_angle);
	data->player.plane_y = tmp_plane_x * sin(-rotate_angle)
		+ data->player.plane_y * cos(-rotate_angle);
	return (1);
}

/**
 * @brief update the image when player move
 * @param data the data to update
 * @note 1. check if player move then render the image
*/
int	update_image(t_data *data)
{
	player_movement(data);
	render_the_image(data);
	return (0);
}
