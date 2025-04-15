/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/14 17:39:58 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	make_grid_map(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	data->map.width += 1;
	data->map.height += 1;
	data->map.grid_map = malloc(sizeof(char *) * (data->map.height + 2));
	while (i < data->map.height)
	{
		data->map.grid_map[i] = malloc(sizeof(char) * (data->map.width));
		i++;
	}
	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width)
		{
			// printf("%d %d\n", i, j);
			data->map.grid_map[i][j] = '0';
			j++;
		}
		data->map.grid_map[i][j] = '\0';
		i++;
	}
	data->map.grid_map[i] = NULL;
	i = 0;
	while (i < data->map.height - 1)
	{
		j = 0;
		while (j < data->map.width - 1)
		{
			if (data->map.map[i][j] == '1')
			{
				data->map.grid_map[i][j] = '1';
				data->map.grid_map[i][j + 1] = '1';
				data->map.grid_map[i + 1][j] = '1';
				data->map.grid_map[i + 1][j + 1] = '1';
			}
			j++;
		}
		i++;
	}
}

void	print_map(char **map, int height, int width)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int argc, char *argv[])
/*
	t_file file;
	t_bearings bearings;
	t_map map;
	this structs does not free because i need it in the code.
	ft_free_split(data.map.map);
	uncomplete_map(&data, 1);
*/
{
	t_cub3d	data;

	if (argc != 2 || !argv[1][0])
	{
		ft_dprintf(2, "Error\n./cub3d file_name.cup\n");
		return (1);
	}
	check_file_name(argv[1]);
	check_empty_read(argv[1]);
	data.file.all_file = read_map(argv[1]);
	parse_map(&data);
	// print_map(data.map.map, data.map.height, data.map.width);
	// make_grid_map(&data);
	// print_map(data.map.grid_map, data.map.height + 1, data.map.width + 1);
	// print_map(data.map.map, data.map.height, data.map.width);
	// ft_free_split(data.map.map);
	// uncomplete_map(&data, 1);
	handle_drawing(&data.mlx_data, &data);
	ft_free_split(data.map.map);
	uncomplete_map(&data, 2);
	return (0);
}
