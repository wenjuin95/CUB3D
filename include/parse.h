/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:56:20 by chtan             #+#    #+#             */
/*   Updated: 2025/01/24 16:38:23 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// # include <stdlib.h>
// # include <stdio.h>
// # include <unistd.h>
// # include <errno.h>
// # include <stdbool.h>
// # include "cub3d.h"

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

typedef struct s_data	t_data;

// parsing
int		parse(char **av, t_data *data);
int		parse_struct(t_map *map);
t_map	*parse_width(t_data *data);
int		get_width(t_map *map);
char	*remove_nl(char *src);
int		ft_strspn(const char *s, const char *accept);
int		search(char **array, int rows, char *target);

//check
void	check_valid_map_name(char *file, char *type);
bool	is_directory(char *file);
int		check_map_sides(t_map *map, char **map_tab);
void	check_valid_element(t_data *data);
int		check_valid_rgb(int *rgb);
int		check_num_players(char **map);
int		parse_check(t_data *data);
int		check_map_closed(char **map, int rows);
void	check_map(t_data *data);
int		check_map_details(t_data *data);
int	flood_fill_recursive(char **map, int i, int j, int height);
int		flood_fill(char **map, int height);
int		check_enclosed_space(char **map, int rows, t_data *data);
int		check_file(char *file);
void	error_handling(t_map *map);
void	error_handling2(t_map *map);

//convert
int		*set_rgb(char *line);
size_t	convert_rgb_to_hex(int *rgb_tab);
char	**copy_2d_array(char **src, int start, int src_height);

//utils
char	**duplicate_map(char **map, int rows);

#endif
