/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:17:49 by welow             #+#    #+#             */
/*   Updated: 2025/01/24 13:52:49 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief determines which texture to use based on the direction the ray is
 *		  coming from and which side of the wall was hit.
 * @param data the data to be calculated
 * @param ray the ray to be calculated
 * @note 1. if the ray hit a vertical wall
 * @note	a. if the ray is moving to the left
 * @note		i. set the texture index to west
 * @note	b. if the ray is moving to the right
 * @note		i. set the texture index to east
*/
void	get_texture_index(t_data *data, t_raycast *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x < 0)
			data->texture.direction = WEST;
		else
			data->texture.direction = EAST;
	}
	else
	{
		if (ray->dir_y < 0)
			data->texture.direction = NORTH;
		else
			data->texture.direction = SOUTH;
	}
}

/**
 * @breif define the line height to be drawn
 * @param ray the ray to be calculated
 * @param data the data to be calculated
 * @note 1. calculate the line height based on the distance to the wall
 * @note 2. calculate the starting point of the line to be drawn
 * @note 3. calculate the ending point of the line to be drawn
*/
void	define_line_height(t_raycast *ray, t_data *data)
{
	if (ray->wall_dis < 0.0001) // Prevent division by a very small number or zero
        ray->wall_dis = 0.0001;
	ray->line_height = (int)(WIN_HEIGHT / ray->wall_dis);
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->win_height / 2;
	if (ray->draw_end >= data->win_height)
		ray->draw_end = data->win_height - 1;
}

/**
 * @brief define the texture to be drawn
 * @param ray the ray to be calculated
 * @param data the data to be calculated
 * @param player the player to be calculated
 * @note 1. if the ray hit the vertical wall
 * @note	a. calculate the x-coordinate on the texture based on the
 * 			wall hit position
 * @note 2. "floor" is to ensures that the right portion of the texture
 * 			is mapped to the correct position on the wall.
 * @note 3. map the wall to texture of x correctly (tex_x)
 * @note 4. flip the texture if the ray hit the left side of the wall or
 * 			the ray hit the bottom side of the wall to make sure the texture
 * 			is mapped correctly
 * @note 5. Determines how much to move vertically in the texture for each
 * 			screen pixel.
 * @note 6. initialize the texture position for the first pixel to be drawn
*/
void	define_texture(t_raycast *ray, t_data *data, t_player *player)
{
	if (ray->side == VERTICAL)
		ray->wall_x = player->pos_y + ray->wall_dis * ray->dir_y;
	else if (ray->side == HORIZONTAL)
		ray->wall_x = player->pos_x + ray->wall_dis * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	data->texture.tex_x = (int)(ray->wall_x * data->texture.width);
	if ((ray->side == VERTICAL && ray->dir_x < 0)
		|| (ray->side == HORIZONTAL && ray->dir_y > 0))
		data->texture.tex_x = data->texture.width
			- data->texture.tex_x - 1;
	data->texture.step = 1.0 * data->texture.height / ray->line_height;
	data->texture.position = (ray->draw_start - data->win_height / 2
			+ ray->line_height / 2) * data->texture.step;
}

/**
 * @brief update the texture pixel based on raycast result
 * @param data the data to be calculated
 * @param tex the texture to be calculated
 * @param ray the ray to be calculated
 * @param x the x coordinate of the screen width
 * @note 1. get the texture index based of the direction of the ray
 * @note 2. define the line height to be drawn
 * @note 3. define the texture to be drawn
 * @note 4. loop through the line to be drawn from start to end
 * @note 5. calculate the y coordinate on the texture
 * @note 6. update the texture position
 * @note 7. get the color from the texture
 * @note 8. set the color to the pixel
 * @note 9. move to the next line
*/
void	update_texture_pixel(t_data *data, t_tex *tex, t_raycast *ray, int x)
{
	int	y;
	int	color;

	get_texture_index(data, ray);
	define_line_height(ray, data);
	define_texture(ray, data, &data->player);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex->tex_y = (int)tex->position % (tex->width);
		tex->position += tex->step;
		if (tex->tex_y < 0 || tex->tex_y >= tex->height || tex->tex_x < 0 || tex->tex_x >= tex->width)
			return;
		color = data->texture.data[tex->direction][tex->width * tex->tex_y + tex->tex_x];
		data->texture.pixel[y][x] = color;
		y++;
	}
}
