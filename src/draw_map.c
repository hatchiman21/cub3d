/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:19:52 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/14 19:44:37 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_line(float x0, float y0, float x1, float y1, int color, t_mlx_cube3d *mlx_data)
{
	float	dx;
	float	dy;
	float	steps;
	float	x_inc;
	float	y_inc;

	dx = x1 - x0;
	dy = y1 - y0;
	steps = fmax(fabs(dx), fabs(dy));
	x_inc = dx / steps;
	y_inc = dy / steps;
	for (int i = 0; i <= steps; i++)
	{
		my_put_pixel(mlx_data->img, x0, y0, color);
		x0 += x_inc;
		y0 += y_inc;
	}
}

void	draw_triangle(float x, float y, int size, float angle,int color, t_mlx_cube3d *mlx_data)
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;

	x1 = x + size * cos(angle);
	y1 = y + size * sin(angle);
	x2 = x + size * cos((angle + 2) * (PI / 3));
	y2 = y + size * sin((angle + 2) * (PI / 3));
	x3 = x + size * cos((angle + 4) * (PI / 3));
	y3 = y + size * sin((angle + 4) * (PI / 3));
	draw_line(x, y, x1, y1, color, mlx_data);
	draw_line(x1, y1, x2, y2, color, mlx_data);
	draw_line(x2, y2, x3, y3, color, mlx_data);
	draw_line(x3, y3, x, y, color, mlx_data);
}

void	draw_cube(float x, float y, int size, int color, t_mlx_cube3d *mlx_data)
{
	int	i;

	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, x + i++, y, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, x, y + i++, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, x + size, y + i++, color);
	i = 0;
	while (i < size)
		my_put_pixel(mlx_data->img, x + i++, y + size, color);
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
			if (map->map[i][j] == '1' && DEBUG != 1)
				draw_cube(j * (BLOCK / 4), i * (BLOCK / 4), BLOCK / 4, 0x0000FFFF, mlx_data);
			else if (map->map[i][j] == '1')
				draw_cube(j * BLOCK, i * BLOCK, BLOCK, 0x0000FFFF, mlx_data);
			j++;
		}
		i++;
	}
}

void	handle_drawing(t_mlx_cube3d *mlx_data, t_cub3d *data)
{
	mlx_data->mlx = mlx_init(CUB_WIDTH, CUB_HEIGHT, "game", true);
	mlx_data->img = mlx_new_image(mlx_data->mlx, CUB_WIDTH, CUB_HEIGHT);\
	determine_init_angle(data);
	data->player.x *= BLOCK;
	data->player.y *= BLOCK;
	mlx_image_to_window(mlx_data->mlx, mlx_data->img, 0, 0);
	mlx_loop_hook(mlx_data->mlx, ft_draw_loop, data);
	mlx_loop(mlx_data->mlx);
	mlx_delete_image(mlx_data->mlx, mlx_data->img);
	mlx_terminate(mlx_data->mlx);
}
