/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_check_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:23:38 by chtan             #+#    #+#             */
/*   Updated: 2025/01/24 16:46:35 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * error handling to check is it the map is closed by wall
 * flood fill will start when there is a space in the map
 */
int	check_enclosed_space(char **map, int rows, t_data *data)
{
	char	**temp_map;

	temp_map = duplicate_map(map, rows);
	if (temp_map == NULL)
		return (1);
	if (flood_fill_recursive(temp_map, data->player.pos_x, data->player.pos_y, rows) == 1)
	{
		free_array((void **)temp_map);
		return (1);
	}
	free_array((void **)temp_map);
	return (0);
}

//int	flood_fill(char **map, int height)
//{
//	int	i;
//	int	j;

//	i = 0;
//	while (map[i])
//	{
//		j = 0;
//		while (map[i][j])
//		{
//			if (map[i][j] == ' ')
//			{
//				printf("flood_fill_recursive: %d\n", flood_fill_recursive(map, i, j, height));
//				if (flood_fill_recursive(map, i, j, height) == 1)
//					return (1);
//			}
//			j++;
//		}
//		i++;
//	}
//	return (0);
//}

int	flood_fill_recursive(char **map, int i, int j, int height)
{
    // Check boundaries
    if (i < 0 || i >= height || j < 0 || map[i][j] == '\0')
        return 1;

    // Check if the current cell is a wall or already visited
    if (map[i][j] == '1' || map[i][j] == 'v')
        return 0;

    // Mark the current cell as visited
    map[i][j] = 'v';

	if (flood_fill_recursive(map, i - 1, j, height) ||
		flood_fill_recursive(map, i + 1, j, height) ||
		flood_fill_recursive(map, i, j - 1, height) ||
		flood_fill_recursive(map, i, j + 1, height))
		return (1);

    return 0;
}

int	get_width(t_map *map)
{
	int	i;
	int	j;

	if (!map->map || map->map[0] == NULL)
		return (ft_error("Invalid ument structure"), 1);
	i = ft_strlen(map->map[0]);
	j = 0;
	while (++j < map->map_height)
	{
		if (i < ft_strlen(map->map[j]))
			i = ft_strlen(map->map[j]);
	}
	return (i);
}

/**
 * check is file can be open
 */
int	check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_error("Fail to open file1"), exit(1));
	return (0);
}
