/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:22:37 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/15 10:24:58 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
// int	x_offset;
// int	y_offset;

// if ((cos(data->player.angle) * BLOCK) > 0)
// 	x_offset = 1;
// else
// 	x_offset = -1;
// if (sin(data->player.angle) * BLOCK > 0)
// 	y_offset = 1;
// else
// 	y_offset = -1;
// if (y + y_offset >= 0 && x + x_offset >= 0 && data->map.map[y + y_offset][x] == '1' &&  data->map.map[y][x + x_offset] == '1')
// 	return (true);

bool	touch(float px, float py, t_cub3d *data)
{
	int	x;
	int	y;

	x = px / BLOCK;
	y = py / BLOCK;
	if(data->map.map[y][x] == '1')
		return (true);
	// if (px / BLOCK - (float)x > 0.005 && py / BLOCK - (float)y > 0.005)
	// 	printf("px: %f, py: %f, x: %d, y: %d\n", px, py, x, y);
	// if (px / BLOCK - (float)x < 0.05 && py / BLOCK - (float)y < 0.05)
	// 	if (data->map.map[y - 1][x] == '1' && data->map.map[y][x - 1] == '1')
	// 		return (true);
	return(false);
}

// bool touch(float px, float py, t_cub3d *data)
// {
//     // apply padding
//     float test_x = px + (px - floorf(px / BLOCK) * BLOCK < EPSILON ? -EPSILON : 0);
//     float test_y = py + (py - floorf(py / BLOCK) * BLOCK < EPSILON ? -EPSILON : 0);

//     int x = test_x / BLOCK;
//     int y = test_y / BLOCK;
//     if (data->map.map[y][x] == '1')
//         return true;
//     return false;
// }

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
	int		start_y;
	int		end_y;

	if (DEBUG == 1)
		return ;
	distance = calculate_distance(data->player.x, ray_x, data->player.y, ray_y, data);
	height = (BLOCK / distance) * (CUB_WIDTH / 2);
	if (height > CUB_HEIGHT)
		height = CUB_HEIGHT;
	start_y = (CUB_HEIGHT - height) / 2;
	end_y = start_y + height;
	while (start_y < end_y)
		my_put_pixel(data->mlx_data.img, i, start_y++, 0xFF0000FF);
}

void	draw_ray_line(t_cub3d *data, float ray_angle, int i)
{
	float	rayDirX;
	float	rayDirY;
	int		stepX;
	int		stepY;	
	float	sideDistX;
	float	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int	mapX;
	int	mapY;
	int	side;

	mapX = (int)data->player.x / BLOCK;
	mapY = (int)data->player.y / BLOCK;
	rayDirX = cos(ray_angle);
	rayDirY = sin(ray_angle);
	deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
	deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);


	//what direction to step in x or y-direction (either +1 or -1)
	//calculate step and initial sideDist
	if(rayDirX < 0)
	{
	  stepX = -1;
	  sideDistX = ((data->player.x / BLOCK) - mapX) * deltaDistX;
	}
	else
	{
	  stepX = 1;
	  sideDistX = (mapX + 1.0 - (data->player.x / BLOCK)) * deltaDistX;
	}
	if(rayDirY < 0)
	{
	  stepY = -1;
	  sideDistY = ((data->player.y / BLOCK) - mapY) * deltaDistY;
	}
	else
	{
	  stepY = 1;
	  sideDistY = (mapY + 1.0 - (data->player.y / BLOCK)) * deltaDistY;
	}
	//perform DDA
	while(1)
	{
	  //jump to next map square, either in x-direction, or in y-direction
	  if(sideDistX < sideDistY)
	  {
		sideDistX += deltaDistX;
		mapX += stepX;
		side = 0;
	  }
	  else
	  {
		sideDistY += deltaDistY;
		mapY += stepY;
		side = 1;
	  }
	  //Check if ray has hit a wall
	  if(data->map.map[mapY][mapX] == '1') break;
	}
	// (void)i;
	// (void)side;
	// draw_3d_ray_line(ray_x, ray_y, i, data);
	// double	height;
	double	distance;
	// int		start_y;
	// int		end_y;
	
	// // if (DEBUG == 1)
	// // 	return ;
	if(side == 0) distance = (mapX - (data->player.x / BLOCK) + (1 - stepX) / 2) / rayDirX;
	else          distance = (mapY - (data->player.y / BLOCK) + (1 - stepY) / 2) / rayDirY;
	int lineHeight = (int)(CUB_HEIGHT / distance);

	if (lineHeight > CUB_HEIGHT)
		lineHeight = CUB_HEIGHT;
	//calculate lowest and highest pixel to fill in current stripe
	int drawStart = -lineHeight / 2 + CUB_HEIGHT / 2;
	if(drawStart < 0) drawStart = 0;
	int drawEnd = lineHeight / 2 + CUB_HEIGHT / 2;
	if(drawEnd >= CUB_HEIGHT) drawEnd = CUB_HEIGHT - 1;
	// printf("height: %f, distance: %f\n", height, distance);
	while (drawStart <= drawEnd)
		my_put_pixel(data->mlx_data.img, i, drawStart++, 0xFFFFFFFF);
}
