/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:33:34 by chtan             #+#    #+#             */
/*   Updated: 2025/01/23 15:20:18 by welow            ###   ########.fr       */
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
		return (ft_error("File is a directory "), -1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		(ft_error("Fail to open file"), exit(1));
	line = get_next_line(fd);
	while (line != NULL)
	{
		lines_num++;
		free(line);
		line = get_next_line(fd);
	}
	if (lines_num == 0)
		(ft_error("Map file is empty"), exit(1));
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
		(ft_error("Fail to open file"), exit(1));
	map = (char **)malloc(sizeof(char *) * (lines_num + 1));
	if (!map)
		return (ft_error("Fail to allocate memory"), (NULL));
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
	if (data->map.file_height == -1)
		(ft_error("Fail to get line number"), clean_and_exit(data));
	data->map.file = read_map_file(data->map_add, data->map.file_height);
	if (!data->map.file)
		(ft_error("Fail to read map file"), clean_and_exit(data));
	parse_struct(&data->map);
	parse_check(data);
	init_player_dir(data);
	return (0);
}
