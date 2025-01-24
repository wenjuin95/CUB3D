/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 21:48:19 by welow             #+#    #+#             */
/*   Updated: 2025/01/24 15:57:03 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * @brief draw a square in the minimap
 * @param data get the image container, x and y coordinate and color
 * @param x x coordinate
 * @param y y coordinate
 * @param color color of the square
 * @note 1. loop through the square
 * @note 2. then put the color to the pixel
*/
void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SIZE)
		{
			color_pixel_put(&data->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void draw_border(t_data *data, int width, int height, int color)
{
	int	x;
	int	y;

	y = 0;
	while(y < height)
	{
		x = 0;
		while (x < width)
		{
			color_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

/**
 * @brief render the minimap
 * @param data get the map layout and player position
 * @note 1. loop through the map layout
 * @note 2. if the map layout is '1' then draw the wall
 * @note 3. if the map layout is '0' then draw the floor
 * @note 4. if the map layout is 'P' then draw the player
*/
void	render_minimap(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;

	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == '1')
				draw_square(data, j * MINIMAP_SIZE, i * MINIMAP_SIZE,
					MINIMAP_FLOOR);
			else if (((int)data->player.pos_x == j && (int)data->player.pos_y
					== i)
				|| data->map.map[i][j] == 'P')
				draw_square(data, j * MINIMAP_SIZE, i * MINIMAP_SIZE,
					MINIMAP_PLAYER);
			j++;
		}
		i++;
	}
	//draw_square(data, data->player.pos_x * MINIMAP_SIZE,
	//	data->player.pos_y * MINIMAP_SIZE, MINIMAP_PLAYER);
}
