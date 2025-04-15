/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:22:37 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/15 14:19:26 by aatieh           ###   ########.fr       */
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
	// if (px / BLOCK - (float)x > 0.005 && py / BLOCK - (float)y > 0.005)
	// 	printf("px: %f, py: %f, x: %d, y: %d\n", px, py, x, y);
	// if (px / BLOCK - (float)x < 0.05 && py / BLOCK - (float)y < 0.05)
	// 	if (data->map.map[y - 1][x] == '1' && data->map.map[y][x - 1] == '1')
	// 		return (true);
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

void	calculate_step(t_ray *ray, t_cub3d *data)
{
	if(ray->rayDirX < 0)
	{
	  ray->stepX = -1;
	  ray->sideDistX = ((data->player.x / BLOCK) - ray->mapX) * ray->deltaDistX;
	}
	else
	{
	  ray->stepX = 1;
	  ray->sideDistX = (ray->mapX + 1.0 - (data->player.x / BLOCK)) * ray->deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
	  ray->stepY = -1;
	  ray->sideDistY = ((data->player.y / BLOCK) - ray->mapY) * ray->deltaDistY;
	}
	else
	{
	  ray->stepY = 1;
	  ray->sideDistY = (ray->mapY + 1.0 - (data->player.y / BLOCK)) * ray->deltaDistY;
	}
}

void	perform_DDA(t_ray *ray, t_cub3d *data)
{
	while(1)
	{
	  if(ray->sideDistX < ray->sideDistY)
	  {
		ray->sideDistX += ray->deltaDistX;
		ray->mapX += ray->stepX;
		ray->side = 0;
	  }
	  else
	  {
		ray->sideDistY += ray->deltaDistY;
		ray->mapY += ray->stepY;
		ray->side = 1;
	  }
	  if(data->map.map[ray->mapY][ray->mapX] == '1')
	  	break;
	}
}

uint32_t	text_color(t_ray *ray, t_cub3d *data)
{
	(void)data;
	if (ray->side == 0 && ray->rayDirX > 0)
		return (0xFF0000FF);
	else if (ray->side == 0 && ray->rayDirX < 0)
		return (0x00FF00FF);
	else if (ray->side == 1 && ray->rayDirY > 0)
		return (0x0000FFFF);
	else
		return (0x00FFFFFF);
	// mlx_texture_t	*texture;

	// if (ray->side == 0 && ray->rayDirX > 0)
	// 	texture = data->mlx_data.so;
	// else if (ray->side == 0 && ray->rayDirX < 0)
	// 	texture = data->mlx_data.no;
	// else if (ray->side == 1 && ray->rayDirY > 0)
	// 	texture = data->mlx_data.ea;
	// else
	// 	texture = data->mlx_data.we;
	
}

mlx_texture_t	*get_texture(t_ray *ray, t_cub3d *data)
{
	// (void)data;
	// if (ray->side == 0 && ray->rayDirX > 0)
	// 	return (0xFF0000FF);
	// else if (ray->side == 0 && ray->rayDirX < 0)
	// 	return (0x00FF00FF);
	// else if (ray->side == 1 && ray->rayDirY > 0)
	// 	return (0x0000FFFF);
	// else
	// 	return (0x00FFFFFF);
	// mlx_texture_t	*texture;

	if (ray->side == 0 && ray->rayDirX > 0)
		return (data->mlx_data.so);
	else if (ray->side == 0 && ray->rayDirX < 0)
		return (data->mlx_data.no);
	else if (ray->side == 1 && ray->rayDirY > 0)
		return (data->mlx_data.ea);
	else
		return (data->mlx_data.we);
}

void	draw_vertical_line(t_ray *ray, t_cub3d *data, int i)
{
	double	distance;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

	if (ray->side == 0)
		distance = (ray->mapX - (data->player.x / BLOCK)
		+ (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		distance = (ray->mapY - (data->player.y / BLOCK)
		+ (1 - ray->stepY) / 2) / ray->rayDirY;
	lineHeight = (int)(CUB_HEIGHT / distance);
	// if (lineHeight > CUB_HEIGHT)
	// 	lineHeight = CUB_HEIGHT;
	drawStart = -lineHeight / 2 + CUB_HEIGHT / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + CUB_HEIGHT / 2;
	if(drawEnd >= CUB_HEIGHT)
		drawEnd = CUB_HEIGHT - 1;
	mlx_texture_t	*texture;
	int texX;
	double wallX; //where exactly the wall was hit
	uint32_t color;
	double step;
	double texPos;
	int texY;

	if(ray->side == 0)
		wallX = data->player.y / BLOCK + distance * ray->rayDirY;
	else
		wallX = data->player.x / BLOCK + distance * ray->rayDirX;
	wallX -= floor((wallX));
	texture = get_texture(ray, data);
	texX = (int)(wallX * (double)(texture->width));
	if (ray->side == 0 && ray->rayDirX > 0)
		texX = texture->width - texX - 1;

	else if (ray->side == 1 && ray->rayDirY < 0)
	{
		texX = texture->width - texX - 1;
	}
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * texture->width / lineHeight;
	// Starting texture coordinate
	texPos = (drawStart - (CUB_HEIGHT - lineHeight) / 2) * step;
	while (drawStart <= drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (texture->height - 1) in case of overflow
		texY = (int)texPos & (texture->width - 1);
		texPos += step;
		if (texX < 0) texX = 0;
	if (texX >= (int)texture->width) texX = (int)texture->width - 1;
	if (texY < 0) texY = 0;
	if (texY >= (int)texture->height) texY = (int)texture->height - 1;
		  int pixel_index = (texY * texture->width + texX) * 4;
		  	uint8_t r = texture->pixels[pixel_index + 0];
			uint8_t g = texture->pixels[pixel_index + 1];
			uint8_t b = texture->pixels[pixel_index + 2];
			uint8_t a = texture->pixels[pixel_index + 3];
			color = (r << 24) | (g << 16) | (b << 8) | a;
			my_put_pixel(data->mlx_data.img, i, drawStart++, color);
		}
// 	float zoom_h = 3.5;
// 	for (uint32_t y = 0; y < texture->height; ++y)
// 	{
// 			int i = (y * texture->width + x) * 4;
// 			uint8_t r = texture->pixels[i + 0];
// 			uint8_t g = texture->pixels[i + 1];
// 			uint8_t b = texture->pixels[i + 2];
// 			uint8_t a = texture->pixels[i + 3];
// 			uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;

// 			// Draw scaled pixel
// 			for (int dy = 0; dy < zoom_h; ++dy)
// 			{
// 					my_put_pixel(data->mlx_data.img, x+ dx, y * zoom_h + dy, color);
// 			}
// 	}
	// while (drawStart <= drawEnd)
	// 	my_put_pixel(data->mlx_data.img, i, drawStart++, text_color(ray, data));
}

void	draw_ray_line(t_cub3d *data, float ray_angle, int i)
{
	t_ray	ray;

	ray.mapX = (int)data->player.x / BLOCK;
	ray.mapY = (int)data->player.y / BLOCK;
	ray.rayDirX = cos(ray_angle);
	ray.rayDirY = sin(ray_angle);
	if (ray.rayDirX == 0)
		ray.deltaDistX = 1e30;
	else
		ray.deltaDistX = fabs(1 / ray.rayDirX);
	if (ray.rayDirY == 0)
		ray.deltaDistY = 1e30;
	else
		ray.deltaDistY = fabs(1 / ray.rayDirY);
	calculate_step(&ray, data);
	perform_DDA(&ray, data);
	draw_vertical_line(&ray, data, i);
}
