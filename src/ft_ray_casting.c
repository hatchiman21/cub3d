/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:22:37 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/14 06:28:47 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	touch(float px, float py, t_cub3d *data)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if(data->map.map[y][x] == '1')
		return (true);
	return(false);
}

float	calculate_distance(float x1, float x2, float y1, float y2, t_cub3d *data)
{
	float	del_x = x2 - x1;
	float	del_y = y2 - y1;
	float	angle = atan2(del_y, del_x) - data->player.angle;
	float	distance = sqrt(pow((x2) - (data->player.x), 2) + pow((y2)
		- (data->player.y) , 2)) * cos(angle);
	return (distance);
}

void	draw_3d_ray_line(float ray_x, float ray_y, int i, t_cub3d *data)
{
	float	height;
	float	distance;

	distance = calculate_distance(data->player.x, ray_x, data->player.y, ray_y, data);
	height = (BLOCK / distance) * (CUB_WIDTH / 2);
	if (height > CUB_HEIGHT)
		height = CUB_HEIGHT;
	int	start_y = (CUB_HEIGHT - height) / 2;
	int	end_y = start_y + height;
	while (start_y < end_y && DEBUG != 1)
		my_put_pixel(data->mlx_data.img, i, start_y++, 0xFF0000FF);
}

void	draw_ray_line(t_cub3d *data, float start_x, int i)
{
	float	cos_angle;
	float	sin_angle;
	float	ray_x;
	float	ray_y;

	cos_angle = cos(start_x);
	sin_angle = sin(start_x);
	ray_x = data->player.x;
	ray_y = data->player.y;
	while (!touch(ray_x, ray_y, data))
	{
		if (DEBUG)
			my_put_pixel(data->mlx_data.img, ray_x / 4, ray_y / 4, 0xFFFF00FF);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	draw_3d_ray_line(ray_x, ray_y, i, data);
}
