/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 12:30:22 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	save_textures(t_cub3d *data)
{
	data->mlx_data.no = mlx_load_png(data->bearings.no);
	data->mlx_data.so = mlx_load_png(data->bearings.so);
	data->mlx_data.we = mlx_load_png(data->bearings.we);
	data->mlx_data.ea = mlx_load_png(data->bearings.ea);
	if (!data->mlx_data.no || !data->mlx_data.so
		|| !data->mlx_data.we || !data->mlx_data.ea)
	{
		ft_dprintf(2, "Error\nFailed to load textures\n");
		uncomplete_map(data, 0);
	}
	free(data->bearings.ea);
	free(data->bearings.no);
	free(data->bearings.so);
	free(data->bearings.we);
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
	save_textures(&data);
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
