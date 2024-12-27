/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow < welow@student.42kl.edu.my>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2024/12/27 00:01:43 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/**
 * get the number of lines in the file
 * for read the file
 */
static int	get_line_nb(char *file)
{
	int		fd;
	int		lines_num;
	char	*line;

	lines_num = 0;
	if (is_directory(file))
		return (perror("File is a directory "), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror("Fail to open file"), exit(1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines_num++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines_num == 0)
		perror("Map file is empty"), exit(1);
	close(fd);
	return (lines_num);
}

/**
 * read the file and store the map in a 2d array
 */
static char	**read_map_file(char *file, int lines_num)
{
	char	**map;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1 || lines_num <= 0)
		perror("Fail to open file"), exit(1);
	map = (char **)malloc(sizeof(char *) * (lines_num + 1));
	if (!map)
		return (perror("Fail to allocate memory"), (NULL));
	i = 0;
	while (i <= lines_num)
	{
		map[i] = get_next_line(fd);
		if (!map[i])
			break ;
		i++;
	}
	map[i] = NULL;
	close(fd);
	return (map);
}

t_map	*parse_width(t_data *data)
{
	t_map	*tmp;
	int		i;

	i = 0;
	tmp = &data->map;
	if (tmp->map == NULL)
		ft_error("Fail to allocate memory12");
	tmp->array_width = (int *)malloc(sizeof(int) * tmp->map_height);
	if (!tmp->array_width)
		ft_error("Fail to allocate memory for map_width");
	while (i < tmp->map_height)
	{
		tmp->array_width[i] = ft_strlen(data->map.map[i]);
		i++;
	}
	return (tmp);
}

int	get_width(t_map *map)
{
	int	i;
	int	j;

	if (!map->map || map->map[0] == NULL)
		return (ft_error("Invalid ument structure"), 1);
	i = ft_strlen(map->map[0]);
	j = 0;
	for(int k = 0; k < map->map_height; k++)
	{
		printf("%s\n", map->map[k]);
	}
	while (++j < map->map_height)
	{
		if (i < ft_strlen(map->map[j]))
			i = ft_strlen(map->map[j]);
	}
	return (i);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void check_player_position(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map.map_height)
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'N'
				|| data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'W'
				|| data->map.map[i][j] == 'E')
			{
				data->player.dir = data->map.map[i][j];
				data->player.pos_x = j + 0.5;
				data->player.pos_y = i + 0.5;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	init_north_south(t_data *data)
{
	if (data->player.dir == 'N')
	{
		//player direction face up
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		//player camera plane from left
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (data->player.dir == 'S')
	{
		//player direction face down
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		//player camera plane from left
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

void	init_east_west(t_data *data)
{
	if (data->player.dir == 'E')
	{
		//player direction face right
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		//player camera plane from left
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (data->player.dir == 'W')
	{
		//player direction face left
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		//player camera plane from left
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	init_player_dir(t_data *data)
{
	init_north_south(data);
	init_east_west(data);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int check_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error("Fail to open file1"), exit(1);
	return (0);
}

int parse_check(t_data *data)
{
	if (check_map_closed(data->map.map, data->map.map_height) == 1)
		return (ft_error("Map not surrounded by wall"), 1);
	if (check_file(data->map.south) == 1 || check_file(data->map.north) == 1
		|| check_file(data->map.east) == 1
		|| check_file(data->map.west) == 1)
		exit(1);
	if (check_num_players(data->map.map) == 1)
		return (ft_error("Invalid number of players"), 1);
	check_valid_element(data);
	check_player_position(data);
	return (0);
}

/**
 * this function is the main function of parsing
 * first parse the argument into struct (map address)
 * check the file name (need to end with .cub)
 * then read the file and store the map in a 2d array
 * lastly read the 2d array and parse each line into different variable
 * error handling
 */
int	parse(char **av, t_data *data)
{
	data->map_add = ft_strdup(av[1]);
	check_valid_map_name(data->map_add, ".cub");
	data->map.file_height = get_line_nb(data->map_add);
	if(data->map.file_height == -1)
		return (ft_error("Fail to get line number"), 1);
	data->map.file = read_map_file(data->map_add, data->map.file_height);
	if (!data->map.file)
		return (ft_error("Fail to read map file"), 1);
	parse_struct(&data->map);
	// parse_check(data);
	check_player_position(data);
	init_player_dir(data);
	return (0);
}