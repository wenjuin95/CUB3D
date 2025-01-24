/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welow <welow@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:21:52 by chtan             #+#    #+#             */
/*   Updated: 2025/01/24 11:08:27 by welow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *str)
{
	printf ("\033[0;32mError : %s\033[0m\n", str);
}

size_t	ft_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*remove_nl(char *src)
{
	int	len;

	len = ft_strlen(src);
	if (src[len - 1] == '\n')
		src[len - 1] = '\0';
	return (src);
}

char	**copy_2d_array(char **src, int start, int src_height)
{
	int		j;
	char	**dest;

	j = 0;
	dest = malloc(sizeof(char *) * (src_height - start + 1));
	while (start < src_height)
	{
		dest[j] = ft_strdup(remove_nl(src[start]));
		start++;
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

int	ft_strspn(const char *s, const char *accept)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (*s)
	{
		while (accept[i] && *s != accept[i])
			i++;
		if (accept[i] == '\0')
			return (count);
		i = 0;
		count++;
		s++;
	}
	return (count);
}
