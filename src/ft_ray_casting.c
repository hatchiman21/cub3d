/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ray_casting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:22:37 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/15 18:52:04 by aatieh           ###   ########.fr       */
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

mlx_texture_t	*get_texture(t_ray *ray, t_cub3d *data)
{
	if (ray->side == 0 && ray->rayDirX > 0)
		return (data->mlx_data.so);
	else if (ray->side == 0 && ray->rayDirX < 0)
		return (data->mlx_data.no);
	else if (ray->side == 1 && ray->rayDirY > 0)
		return (data->mlx_data.ea);
	else
		return (data->mlx_data.we);
}

// void	handle_texture(t_ray *ray, t_cub3d *data, mlx_texture_t *texture)
// {
// 	t_texture	tex;

// 	if(ray->side == 0)
// 		tex.wallX = data->player.y / BLOCK + distance * ray->rayDirY;
// 	else
// 		tex.wallX = data->player.x / BLOCK + distance * ray->rayDirX;
// 	tex.wallX -= floor((tex.wallX));
// 	texture = get_texture(ray, data);
// 	tex.texX = (int)(tex.wallX * (double)(tex.texture->width));
// 	if (ray->side == 0 && ray->rayDirX > 0)
// 		tex.texX = tex.texture->width - tex.texX - 1;

// 	else if (ray->side == 1 && ray->rayDirY < 0)
// 	{
// 		tex.texX = tex.texture->width - tex.texX - 1;
// 	}
// 	step = 1.0 * tex.texture->width / lineHeight;
// 	tex.texPos = (drawStart - (CUB_HEIGHT - lineHeight) / 2) * step;
// 	while (drawStart <= drawEnd)
// 	{
// 		tex.texY = (int)tex.texPos & (tex.texture->width - 1);
// 		tex.texPos += step;
// 		if (tex.texX < 0) tex.texX = 0;
// 	if (tex.texX >= (int)tex.texture->width) tex.texX = (int)tex.texture->width - 1;
// 	if (tex.texY < 0) tex.texY = 0;
// 	if (tex.texY >= (int)tex.texture->height) tex.texY = (int)tex.texture->height - 1;
// 		  int tex.pixel_index = (tex.texY * tex.texture->width + tex.texX) * 4;
// 		  	uint8_t r = tex.texture->pixels[pixel_index + 0];
// 			uint8_t g = tex.texture->pixels[pixel_index + 1];
// 			uint8_t b = tex.texture->pixels[pixel_index + 2];
// 			uint8_t a = tex.->pixels[tex.pixel_index + 3];
// 			color = (r << 24) |texture (g << 16) | (b << 8) | a;
// 			my_put_pixel(data->mlx_data.img, i, drawStart++, color);
// 		}
// }

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
	drawStart = -lineHeight / 2 + CUB_HEIGHT / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + CUB_HEIGHT / 2;
	if(drawEnd >= CUB_HEIGHT)
		drawEnd = CUB_HEIGHT - 1;
	mlx_texture_t	*texture;
	int texX;
	double wallX;
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
	step = 1.0 * texture->width / lineHeight;
	texPos = (drawStart - (CUB_HEIGHT - lineHeight) / 2) * step;
	while (drawStart <= drawEnd)
	{
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
