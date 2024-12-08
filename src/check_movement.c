/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:38:25 by welow             #+#    #+#             */
/*   Updated: 2024/12/08 21:49:40 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief check the position can be move or not
 * @param data the data
 * @param move_x the x position to move
 * @param move_y the y position to move
 * @return 1 if player move, 0 if player not move
 * @note 1. check if the player chg position the current position is '0'
*/
int	check_move(t_data *data, double move_x, double move_y)
{
	int	moved;

	moved = 0;
	if (data->map[(int)data->player.pos_y][(int)move_x] != '1')
	{
		data->map[(int)data->player.pos_y][(int)move_x] = '0';
		data->player.pos_x = move_x;
		moved = 1;
	}
	if (data->map[(int)move_y][(int)data->player.pos_x] != '1')
	{
		data->map[(int)move_y][(int)data->player.pos_x] = '0';
		data->player.pos_y = move_y;
		moved = 1;
	}
	return (moved);
}

/**
 * @brief rotate the player right (before is left)
 * @param data the data
 * @return 1 if player rotate, 0 if player not rotate
*/
int	rotate_right(t_data *data)
{
	double	tmp_x;

	tmp_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(ROTATE_SPEED)
		- data->player.dir_y * sin(ROTATE_SPEED);
	data->player.dir_y = tmp_x * sin(ROTATE_SPEED) + data->player.dir_y
		* cos(ROTATE_SPEED);
	tmp_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(ROTATE_SPEED)
		- data->player.plane_y * sin(ROTATE_SPEED);
	data->player.plane_y = tmp_x * sin(ROTATE_SPEED) + data->player.plane_y
		* cos(ROTATE_SPEED);
	return (1);
}

/**
 * @brief rotate the player left (before is right)
 * @param data the data
 * @return 1 if player rotate, 0 if player not rotate
*/
int	rotate_left(t_data *data)
{
	double	tmp_x;

	tmp_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(-ROTATE_SPEED)
		- data->player.dir_y * sin(-ROTATE_SPEED);
	data->player.dir_y = tmp_x * sin(-ROTATE_SPEED) + data->player.dir_y
		* cos(-ROTATE_SPEED);
	tmp_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(-ROTATE_SPEED)
		- data->player.plane_y * sin(-ROTATE_SPEED);
	data->player.plane_y = tmp_x * sin(-ROTATE_SPEED) + data->player.plane_y
		* cos(-ROTATE_SPEED);
	return (1);
}

/**
 * @brief update the image when player move
 * @param data the data to update
 * @note 1. check if player move then render the image
*/
int	update_image(t_data *data)
{
	if (player_movement(data) != 0)
	{
		render_the_image(data);
		//debug_raycast(&data->ray); //debug
	}
	return (0);
}