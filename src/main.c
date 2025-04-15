/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:32:26 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 20:29:57 by aatieh           ###   ########.fr       */
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
	if (data->moon.f[0])
		mlx_delete_texture(data->moon.f[0]);
	if (data->moon.f[1])
		mlx_delete_texture(data->moon.f[1]);
	if (data->moon.f[2])
		mlx_delete_texture(data->moon.f[2]);
	if (data->moon.f[3])
		mlx_delete_texture(data->moon.f[3]);
}

void	save_textures(t_cub3d *data)
{
	data->mlx_data.no = mlx_load_png(data->bearings.no);
	data->mlx_data.so = mlx_load_png(data->bearings.so);
	data->mlx_data.we = mlx_load_png(data->bearings.we);
	data->mlx_data.ea = mlx_load_png(data->bearings.ea);
	data->moon.f[0] = mlx_load_png("./texture/moon/moon_frame_00.png");
	data->moon.f[1] = mlx_load_png("./texture/moon/moon_frame_01.png");
	data->moon.f[2] = mlx_load_png("./texture/moon/moon_frame_02.png");
	data->moon.f[3] = mlx_load_png("./texture/moon/moon_frame_03.png");
	data->moon.frame = 0;
	data->moon.x = 500;
	data->moon.y = 0;
	if (!data->mlx_data.no || !data->mlx_data.so
		|| !data->mlx_data.we || !data->mlx_data.ea
		|| !data->moon.f[0] || !data->moon.f[1]
		|| !data->moon.f[2] || !data->moon.f[3])
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
