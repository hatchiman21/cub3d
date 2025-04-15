/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 19:11:55 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	delete_textures(t_cub3d *data)
{
	if (data->mlx_data.no)
		mlx_delete_texture(data->mlx_data.no);
	if (data->mlx_data.so)
		mlx_delete_texture(data->mlx_data.so);
	if (data->mlx_data.we)
		mlx_delete_texture(data->mlx_data.we);
	if (data->mlx_data.ea)
		mlx_delete_texture(data->mlx_data.ea);
}

void	save_textures(t_cub3d *data)
{
	data->mlx_data.no = mlx_load_png(data->bearings.no);
	data->mlx_data.so = mlx_load_png(data->bearings.so);
	data->mlx_data.we = mlx_load_png(data->bearings.we);
	data->mlx_data.ea = mlx_load_png(data->bearings.ea);
	if (!data->mlx_data.no || !data->mlx_data.so
		|| !data->mlx_data.we || !data->mlx_data.ea)
	{
		delete_textures(data);
		uncomplete_map(data, 2);
	}
}

int	main(int argc, char *argv[])
{
	t_cub3d	data;

	if (argc != 2 || !argv[1][0])
	{
		ft_putstr_fd("Error\n./cub3d file_name.cup\n", 2);
		return (1);
	}
	check_file_name(argv[1]);
	check_empty_read(argv[1]);
	data.file.all_file = read_map(argv[1]);
	parse_map(&data);
	save_textures(&data);
	handle_drawing(&data.mlx_data, &data);
	uncomplete_map(&data, 3);
	return (0);
}
