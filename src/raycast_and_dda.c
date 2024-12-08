/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_and_dda.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 09:28:44 by welow             #+#    #+#             */
/*   Updated: 2024/12/06 18:11:08 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief calculate the ray direction and delta distance
 * @param x the x coordinate of the screen width
 * @param ray the ray to be calculated
 * @param player the player to be calculated
 * @note 1. calculate the ray direction from the player to the wall
 * @note 	a. camera: calculate how far left or right this ray is from the center of the camera
 * @note 	b. dir_x: calculate the ray direction of x
 * @note 2. calculate the delta distance ( determine the distance the ray has to travel
 * 			to go from one x-side to the next x-side, or one y-side to the next y-side)
 * @note 	a. delta_dist_x: calculate how far the ray moves in the each grid x
*/
void	calculate_ray_and_grid(int x, t_raycast *ray, t_player *player)
{
	//calculate the ray direction
	ray->camera = 2 * x / (double)WIN_WIDTH - 1; //representing the horizontal position on the camera plane
	ray->dir_x = player->dir_x + player->plane_x * ray->camera; //Sets the x-direction of the ray.
	ray->dir_y = player->dir_y + player->plane_y * ray->camera; //Sets the y-direction of the ray.

	//calculate length of ray from "one x or y-side" to "next x or y-side"
	ray->map_x = (int)player->pos_x; //Sets the x-coordinate of the map square the player is currently in.
	ray->map_y = (int)player->pos_y; //Sets the y-coordinate of the map square the player is currently in.
	ray->delta_dist_x = fabs(1 / ray->dir_x);//Sets the distance the ray has to travel in the x-direction to move from one x-side to the next.
	ray->delta_dist_y = fabs(1 / ray->dir_y);// Sets the distance the ray has to travel in the y-direction to move from one y-side to the next.
}

/**
 * @brief calculate the step and initialize side distance
 * @param ray the ray to be calculated
 * @param player the player to be calculated
*/
void	set_dda(t_raycast *ray, t_player *player)
{
	if (ray->dir_x < 0) //if ray is facing left direction in x axis
	{
		ray->step_x = -1; //ray moves to the left
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x; //Calculates the initial side distance in the x-direction.
	}
	else //if ray is facing right direction in x axis
	{
		ray->step_x = 1; //ray moves to the right
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x; //Calculates the initial side distance in the x-direction.
	}
	if (ray->dir_y < 0) //if ray is facing down direction in y axis
	{
		ray->step_y = -1; //ray move down
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y; //Calculates the initial side distance in the y-direction.
	}
	else //if ray is facing up direction in y axis
	{
		ray->step_y = 1; //ray move up
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y; //Calculates the initial side distance in the y-direction.
	}
}

/**
 * @brief perform DDA algorithm
 * @param data the data to be calculated
 * @param ray the ray to be calculated
 * @note 1. perform DDA algorithm to calculate the distance to the wall
 * @note 	a. if the distance to the next grid x < distance to the next grid y, then
 * 			   move to the next grid x and add the distance to the next grid x
 * @note 	b. if the distance to the next grid y < distance to the next grid x, then
 * 			   move to the next grid y and add the distance to the next grid y
 * @note 	c. if the map is a wall, then hit the wall
*/
void	perform_dda(t_data *data, t_raycast *ray)
{
	int	hit_wall;

	hit_wall = 0;
	while (hit_wall == 0)
	{
		//jump to next map square
		if (ray->side_dist_x < ray->side_dist_y) //Checks if the next grid crossing in the x-direction is closer than the next grid crossing in the y-direction.
		{
			ray->side_dist_x += ray->delta_dist_x; //Moves the ray to the next x-side.
			ray->map_x += ray->step_x; //update the map x (player position) coordinate
			ray->side = VERTICAL_WALL; //set the side to 0 (vertical wall)
		}
		else //If the next grid crossing in the y-direction is closer.
		{
			ray->side_dist_y += ray->delta_dist_y; //Moves the ray to the next y-side
			ray->map_y += ray->step_y; //Updates the map y-coordinate.
			ray->side = HORIZONTAL_WALL; //set the side to 1 (horizontal wall)
		}

		//if next map square is a wall
		if (data->map[ray->map_y][ray->map_x] == '1') //Checks if the ray has hit a wall.
			hit_wall = 1; //Sets the hit_wall variable to 1 to indicate that the ray has hit a wall.
	}
}

/**
 * @brief calculate the line height to draw
 * @param ray the ray to be calculated
 * @param data the data to be calculated
 * @param player the player to be calculated
*/
void	calculate_line_height_to_draw(t_raycast *ray, t_data *data, t_player *player)
{
	//calculate distance of the perpendicular ray
	if (ray->side == VERTICAL_WALL) //Checks if the ray hit a horizontal wall.
		ray->wall_dis = (ray->side_dist_x - ray->delta_dist_x); //Calculates the perpendicular distance to the wall for a horizontal hit.
	else // If the ray hit a vertical wall.
		ray->wall_dis = (ray->side_dist_y - ray->delta_dist_y); //Calculates the perpendicular distance to the wall for a vertical hit.

	//calculate height of line to draw on screen
	ray->line_height = (int)(data->win_height / ray->wall_dis); //calculate the line height to be draw on screen

	//calculate lowest and highest pixel to fill in current line
	ray->draw_start = -(ray->line_height) / 2 + data->win_height / 2; //calculate the start point to draw the line
	if (ray->draw_start < 0) //ensure the starting point is not above the window
		ray->draw_start = 0; //Sets the starting position to the top of the window if it is
	ray->draw_end = ray->line_height / 2 + data->win_height / 2; //calculate the end point to draw the line
	if (ray->draw_end >= data->win_height) //Ensures the ending position is not below the window.
		ray->draw_end = data->win_height - 1; //Sets the ending position to the bottom of the window if it exceeds the window height

	//calculate value of wall_x
	if (ray->side == VERTICAL_WALL) //Checks if the ray hit a horizontal wall.
		ray->wall_x = player->pos_y + ray->wall_dis * ray->dir_y; //Calculates the exact x-coordinate of the wall hit for a horizontal wall.
	else // If the ray hit a vertical wall.
		ray->wall_x = player->pos_x + ray->wall_dis * ray->dir_x; //Calculates the exact x-coordinate of the wall hit for a vertical wall.
	ray->wall_x -= floor(ray->wall_x); //Normalizes the wall hit coordinate to a value between 0 and 1.
}

int	raycasting(t_player *player, t_data *data)
{
	int		x;

	x = 0;
	while (x < data->win_width)
	{
		calculate_ray_and_grid(x, &data->ray, player);
		set_dda(&data->ray, player);
		perform_dda(data, &data->ray);
		calculate_line_height_to_draw(&data->ray, data, player);
		update_texture_pixel(data, &data->texture, &data->ray, x);
		x++;
	}
	return (0);
}