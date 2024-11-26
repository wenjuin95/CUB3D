/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:56:54 by chtan             #+#    #+#             */
/*   Updated: 2024/11/26 10:57:09 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static void	error_handling(t_map *map)
{
	if (!map->north || !map->sout || !map->west || !map->east || !map->sprite
		|| !map->floor || !map->ceiling || !map->map_layout)
		ft_error("Fail to allocate memory");
}

int	parse_struct(t_map *map)
{
	map->mapl_len = map->map_height - 8;
	map->north = cut_first3(map->map[0], ft_strlen(map->map[0]), 3);
	map->sout = cut_first3(map->map[1], ft_strlen(map->map[1]), 3);
	map->west = cut_first3(map->map[2], ft_strlen(map->map[2]), 3);
	map->east = cut_first3(map->map[3], ft_strlen(map->map[3]), 3);
	map->sprite = cut_first3(map->map[4], ft_strlen(map->map[4]), 2);
	map->floor = set_rgb(cut_first3(map->map[5], ft_strlen(map->map[5]), 2));
	map->ceiling = set_rgb(cut_first3(map->map[6], ft_strlen(map->map[6]), 2));
	map->map_layout = copy_2d_array(map->map, 8, map->map_height);
	error_handling(map);
	return (0);
}

char	**copy_2d_array(char **src, int start, int src_height)
{
	int		j;
	char	**dest;

	j = 0;
	dest = malloc(sizeof(char *) * (src_height - start + 1));
	while (start < src_height)
	{
		dest[j] = ft_strdup(src[start]);
		start++;
		j++;
	}
	dest[j] = NULL;
	free_2d(src);
	return (dest);
}

char	*cut_first3(char *s, int len, int start)
{
	int		i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	str = malloc(sizeof(char) * len - 2);
	while (i < len)
	{
		str[j] = s[i];
		j++;
		i++;
	}
	return (str);
}

/**
 * the function is parse the arg to the struct
 */
void	take_arg(int ac, char **av, t_arg *arg)
{
	if (ac != 2)
		ft_error("Wrong number of arguments");
	arg->map_add = ft_strdup(av[1]);
}
