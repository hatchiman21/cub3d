/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:19:52 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/15 21:34:55 by aatieh           ###   ########.fr       */
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

void mouse_handler(double xdelta, double ydelta, void* param)
{
	t_cub3d		*data;
	t_player	*player;

	data = (t_cub3d *)param;
	player = &data->player;
	(void)ydelta;
	if (xdelta < player->x_delta)
		data->player.angle -= ROTATE_SPEED / 1.5;
	else if (xdelta > player->x_delta)
		data->player.angle += ROTATE_SPEED / 1.5;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	else if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
	player->x_delta = xdelta;
}

void	free_mlx_data(t_mlx_cube3d *mlx_data)
{
	if (mlx_data->no)
		mlx_delete_texture(mlx_data->no);
	if (mlx_data->so)
		mlx_delete_texture(mlx_data->so);
	if (mlx_data->we)
		mlx_delete_texture(mlx_data->we);
	if (mlx_data->ea)
		mlx_delete_texture(mlx_data->ea);
	mlx_delete_image(mlx_data->mlx, mlx_data->img);
	mlx_terminate(mlx_data->mlx);
}

void	ft_key_hook(mlx_key_data_t keydata, void* param)
{
	t_cub3d		*data;
	int			next_x;
	int			next_y;

	data = (t_cub3d *)param;
	next_x = data->player.x + SPEED * COLISION  * cos(data->player.angle);
	next_y = data->player.y + SPEED * COLISION  * sin(data->player.angle);
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
	data->player.x *= BLOCK;
	data->player.y *= BLOCK;
	data->player.x_delta = 0;
	mlx_image_to_window(mlx_data->mlx, mlx_data->img, 0, 0);
	mlx_key_hook(mlx_data->mlx, ft_key_hook, data);
	mlx_cursor_hook(mlx_data->mlx, mouse_handler, data);
	mlx_loop_hook(mlx_data->mlx, ft_draw_loop, data);
	mlx_loop(mlx_data->mlx);
	free_mlx_data(mlx_data);
}
