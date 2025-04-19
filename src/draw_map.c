/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:19:52 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/19 21:49:42 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_cube(float xy[2], int size, int color, t_mlx_cube3d *mlx_data)
{
	int	i;

	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0] + i++, xy[1], color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0], xy[1] + i++, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0] + size, xy[1] + i++, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, xy[0] + i++, xy[1] + size, color);
}

void	draw_map(t_map *map, t_mlx_cube3d *mlx_data)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '1')
				draw_cube((float []){j * (BLOCK / 4), i * (BLOCK / 4)},
					BLOCK / 4, 0x0000FFFF, mlx_data);
			else if ((map->map[i][j] == 'D' || map->map[i][j] == 'O'))
				draw_cube((float []){j * (BLOCK / 4), i * (BLOCK / 4)},
					BLOCK / 4, 0x0FF0FFFF, mlx_data);
			j++;
		}
		i++;
	}
}

void	free_mlx_data(t_cub3d *data)
{
	delete_textures(data);
	mlx_delete_image(data->mlx_data.mlx, data->mlx_data.img);
	mlx_terminate(data->mlx_data.mlx);
}

void	ft_open_door(mlx_key_data_t keydata, void *param)
{
	t_cub3d	*data;
	int		next_x;
	int		next_y;

	data = (t_cub3d *)param;
	next_x = data->player.x + COLISION * 1.5 * cos(data->player.angle);
	next_y = data->player.y + COLISION * 1.5 * sin(data->player.angle);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_RELEASE)
	{
		if (data->map.map[next_y / BLOCK][next_x / BLOCK] == 'D')
			data->map.map[next_y / BLOCK][next_x / BLOCK] = 'O';
		else if (data->map.map[next_y / BLOCK][next_x / BLOCK] == 'O')
			data->map.map[next_y / BLOCK][next_x / BLOCK] = 'D';
	}
}

void	handle_drawing(t_mlx_cube3d *mlx_data, t_cub3d *data)
{
	mlx_data->mlx = mlx_init(CUB_WIDTH, CUB_HEIGHT, "game", false);
	if (!mlx_data->mlx)
	{
		delete_textures(data);
		ft_putstr_fd("Error\nFailed to initialize mlx\n", 2);
		uncomplete_map(data, 0);
	}
	mlx_data->img = mlx_new_image(mlx_data->mlx, CUB_WIDTH, CUB_HEIGHT);
	if (!mlx_data->img)
	{
		delete_textures(data);
		mlx_terminate(mlx_data->mlx);
		ft_putstr_fd("Error\nFailed to create image\n", 2);
		uncomplete_map(data, 0);
	}
	determine_init_angle(data);
	data->player.x_delta = 0;
	mlx_image_to_window(mlx_data->mlx, mlx_data->img, 0, 0);
	mlx_key_hook(mlx_data->mlx, ft_open_door, data);
	mlx_cursor_hook(mlx_data->mlx, mouse_handler, data);
	mlx_loop_hook(mlx_data->mlx, ft_draw_loop, data);
	mlx_loop(mlx_data->mlx);
	free_mlx_data(data);
}
