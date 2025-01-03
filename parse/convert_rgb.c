/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:09:46 by chtan             #+#    #+#             */
/*   Updated: 2024/12/30 18:26:19 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

size_t	convert_rgb_to_hex(int *rgb_tab)
{
	size_t	result;
	int		r;
	int		g;
	int		b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	result = ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (result);
}

static int	*copy_to_rgb_array(char **rgb_to_convert, int *rgb)
{
	int	i;

	i = 0;
	while (rgb_to_convert[i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		free(rgb_to_convert[i]);
		i++;
	}
	i = 0;
	free(rgb_to_convert);
	if (check_valid_rgb(rgb) == 1)
		exit(EXIT_FAILURE);
	return (rgb);
}

int	*set_rgb(char *line)
{
	char	**rgb_to_convert;
	int		count;
	int		*rgb;

	count = 0;
	rgb_to_convert = ft_split(line, ',');
	free(line);
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		ft_error("Invalid RGB format");
		exit(EXIT_FAILURE);
	}
	rgb = malloc(sizeof(int) * 3);
	return (copy_to_rgb_array(rgb_to_convert, rgb));
}
