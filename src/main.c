/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chtan <chtan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:57:52 by welow             #+#    #+#             */
/*   Updated: 2024/12/04 11:31:32 by chtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parse.h"

#include <stdio.h>

// static void print_map_struct(const t_map *map)
// {
//     if (!map)
//       return;
//     printf("Map Layout Length: (%d) but (%d)\n", map->mapl_len,
//         map->mapl_len - 1);
//     printf("Map Height: (%d)\n", map->map_height);
// 	printf("map layout width %d", map->map_width);
//     printf("Map Width: ");
//     if (map->map_width)
//     {
//         for (int i = 0; i < map->mapl_len; i++)
//         {
//             printf("(%d)", map->array_width[i]);
//             if (i < map->mapl_len - 1)
//                 printf(", ");
//         }
//         printf("\n");
//     }
//     else
//         printf("(null)\n");
//     printf("North Texture: (%s)\n", map->north ? map->north : "(null)");
//     printf("South Texture: (%s)\n", map->sout ? map->sout : "(null)");
//     printf("West Texture: (%s)\n", map->west ? map->west : "(null)");
//     printf("East Texture: (%s)\n", map->east ? map->east : "(null)");
//     printf("Sprite: (%s)\n", map->sprite ? map->sprite : "(null)");
//     printf("Floor RGB: ");
//     if (map->floor)
//         printf("(%d), (%d), (%d)\n", map->floor[0], map->floor[1], map->floor[2]);
//     else
//         printf("(null)\n");
//     printf("Ceiling RGB: ");
//     if (map->ceiling)
//     printf("(%d), (%d), (%d)\n", map->ceiling[0], map->ceiling[1],
//         map->ceiling[2]);
//     else
//         printf("(null)\n");
//     printf("Map Layout:\n");
//     if (map->map_layout)
//     {
//         for (int i = 0; map->map_layout[i] != NULL; i++)
//             printf("%s", map->map_layout[i]);
//     }
//     else
//         printf("  (null)\n");
//     printf("\n\n");
//     printf("Floor Hex: (0x%zx)\n", map->floor_hex);
//     printf("Ceiling Hex: (0x%zx)\n", map->ceiling_hex);
// }

// static void print_arg_struct(const t_arg *arg)
// {
//     if (!arg)
//         return;
//     printf("\033[1;31mPrinting arg struct:\n\n\n\033[0m");
//     printf("Map Address: (%s)\n", arg->map_add ? arg->map_add : "(null)");
//     printf("Map Struct:\n");
//     print_map_struct(&arg->map);
//     printf("printng end\n");
// }

	// print_arg_struct(&arg);
int	main(int argc, char **argv)
{
	t_arg	arg;

	if (argc == 1)
		return (ft_error("wrong argument/ without argument"), 1);
	initialize_arg(&arg);
	parse(argc, argv, &arg);
	// print_arg_struct(&arg);
    // if (arg.map.map_layout == NULL)
    //     printf("parsing okay\n");
	free_arg(&arg);
	return (0);
}
