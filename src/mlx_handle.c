/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:03:47 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/16 19:15:23 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <stdbool.h>
// // #include "../MLX42/include/MLX42/MLX42.h"

// #define WIDTH 512
// #define HEIGHT 512

// static mlx_image_t* image;
// static mlx_image_t* image2;

// // -----------------------------------------------------------------------------

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_randomize(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				0, // R
// 				0, // G
// 				rand() % 0xFF, // B
// 				0xFF  // A
// 			);
// 			my_put_pixel(image, i, y, color);
// 		}
// 	}
// }

// void ft_block(void* param)
// {
// 	(void)param;
// 	for (uint32_t i = 0; i < image2->width; ++i)
// 	{
// 		for (uint32_t y = 0; y < image2->height; ++y)
// 		{
// 			uint32_t color = ft_pixel(
// 				0xFF, // R
// 				0, // G
// 				0, // B
// 				0xFF  // A
// 			);
// 			my_put_pixel(image2, i, y, color);
// 		}
// 	}
// }

// void ft_hook(void* param)
// {
// 	t_cub3d* data = param;

// 	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(data->mlx_data.mlx);
// 	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_UP))
// 		data->player.y -= SPEED;
// 	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_DOWN))
// 		data->player.y += SPEED;
// 	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_LEFT))
// 		data->player.x -= SPEED;
// 	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_RIGHT))
// 		data->player.x += SPEED;
// }

// // -----------------------------------------------------------------------------

// // int32_t main(void)
// // {
// // 	mlx_t* mlx;

// // 	// Gotta error check this stuff
// // 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// // 	{
// // 		puts(mlx_strerror(mlx_errno));
// // 		return(EXIT_FAILURE);
// // 	}
// // 	if (!(image = mlx_new_image(mlx, 128, 128)))
// // 	{
// // 		mlx_close_window(mlx);
// // 		puts(mlx_strerror(mlx_errno));
// // 		return(EXIT_FAILURE);
// // 	}
// // 	image2 = mlx_new_image(mlx, 128, 128);
// // 	mlx_image_to_window(mlx, image2, 0, 0);
// // 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// // 	{
// // 		mlx_close_window(mlx);
// // 		puts(mlx_strerror(mlx_errno));
// // 		return(EXIT_FAILURE);
// // 	}
// // 	// mlx_loop_hook(mlx, ft_block, mlx);
// // 	ft_block(mlx);
// // 	// mlx_loop_hook(mlx, ft_randomize, mlx);
// // 	// mlx_loop_hook(mlx, ft_hook, mlx);
	
// // 	printf("here\n");
// // 	mlx_loop(mlx);
// // 	mlx_terminate(mlx);
// // 	return (EXIT_SUCCESS);
// // }

// void	detrmine_init_angle(t_cub3d *data)
// {
// 	if (data->player.c == 'W')
// 		data->player.angle = 0 * (PI / 180);
// 	else if (data->player.c == 'S')
// 		data->player.angle = 180 * (PI / 180);
// 	else if (data->player.c == 'A')
// 		data->player.angle = 270 * (PI / 180);
// 	else if (data->player.c == 'D')
// 		data->player.angle = 90 * (PI / 180);
// }

// void	inti_mlx_struct(t_cub3d *data)
// {
// 	data->mlx_data.mlx = mlx_init(1920, 1080, "main", true);
// 	float zoom_h = 3.5;
// 	float zoom_w = 1;
// 	mlx_texture_t* texture = mlx_load_png(data->bearings.no); 
// 	data->mlx_data.img = mlx_new_image(data->mlx_data.mlx, texture->width * zoom_w, texture->height * zoom_h);
// 	for (uint32_t y = 0; y < texture->height; ++y)
// 	{
// 		for (uint32_t x = 0; x < texture->width; ++x)
// 		{
// 			int i = (y * texture->width + x) * 4;
// 			uint8_t r = texture->pixels[i + 0];
// 			uint8_t g = texture->pixels[i + 1];
// 			uint8_t b = texture->pixels[i + 2];
// 			uint8_t a = texture->pixels[i + 3];
// 			uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;

// 			// Draw scaled pixel
// 			for (int dy = 0; dy < zoom_h; ++dy)
// 			{
// 				for (int dx = 0; dx < zoom_w; ++dx)
// 				{
// 					my_put_pixel(data->mlx_data.img, x * zoom_w + dx, y * zoom_h + dy, color);
// 				}
// 			}
// 		}
// 	}
// 	detrmine_init_angle(data);
// 	if (!data->mlx_data.mlx || !data->mlx_data.img)
// 		ft_putstr_fd("error\n", 2);
// }

// void	calc_zoom(float x, float y, float angle, char **map)
// {
// 	float ray_dir_x = cos(angle);
// 	float ray_dir_y = sin(angle);
// 	int step_x, step_y;
// 	float side_dist_x, side_dist_y;
// 	float delta_dist_x = fabs(1 / ray_dir_x);
// 	float delta_dist_y = fabs(1 / ray_dir_y);

// 	// What square are we in?
// 	int map_x = (int)x;
// 	int map_y = (int)y;

// 	// Calculate step and initial side distance
// 	if (ray_dir_x < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = (map_x + 1.0 - x) * delta_dist_x;
// 	}

// 	if (ray_dir_y < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = (map_y + 1.0 - y) * delta_dist_y;
// 	}
// 	int hit = 0;
// 	int side;

// 	while (!hit)
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 			side = 1;
// 		}

// 		// Now (map_x, map_y) is the new grid cell
// 		// Check if there's a wall or object:
// 		if (map[map_y][map_x] == 1)
// 			hit = 1;
// 	}
// }

// void	free_cub_struct(t_cub3d *data)
// {
// 	if (data->mlx_data.mlx && data->mlx_data.img)
// 		mlx_delete_image(data->mlx_data.mlx, data->mlx_data.img);
// 	if (data->mlx_data.mlx)
// 		mlx_terminate(data->mlx_data.mlx);
// }

// void	handle_mlx(t_cub3d *data)
// {
// 	mlx_image_to_window(data->mlx_data.mlx, data->mlx_data.img, 0, 0);
// 	mlx_loop_hook(data->mlx_data.mlx, ft_hook, data);
// 	mlx_loop(data->mlx_data.mlx);
// }

void ft_background(uint32_t start, uint32_t color, mlx_image_t *img)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < CUB_WIDTH)
	{
		j = 0;
		while (j < CUB_HEIGHT / 2)
			my_put_pixel(img, i, start + j++, color);
		i++;
	}
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	if (x > img->width || y > img->height)
		return ;
	mlx_put_pixel(img, x, y, color);
}

void	draw_sprite(t_cub3d *data, mlx_texture_t *texture, t_sprite *sprite)
{
	float zoom_h = 0.5;
	float zoom_w = 0.5;
	for (uint32_t y = 0; y < texture->height; ++y)
	{
		for (uint32_t x = 0; x < texture->width; ++x)
		{
			int i = (y * texture->width + x) * 4;
			uint8_t r = texture->pixels[i + 0];
			uint8_t g = texture->pixels[i + 1];
			uint8_t b = texture->pixels[i + 2];
			uint8_t a = texture->pixels[i + 3];
			uint32_t color = (a << 24) | (r << 16) | (g << 8) | b;

			// Draw scaled pixel
			for (int dy = 0; dy < zoom_h; ++dy)
			{
				for (int dx = 0; dx < zoom_w; ++dx)
				{
					if (color != 0)
						my_put_pixel(data->mlx_data.img, x * zoom_w + dx + sprite->x, y * zoom_h + dy + sprite->y, color);
				}
			}
		}
	}
}

void	ft_draw_loop(void* param)
{
	t_cub3d*	data;
	float		fraction;
	float		ray_angle;
	int			i;

	data = (t_cub3d *)param;
	ft_background(0, ft_pixel(data->arr_ceiling_color[0], data->arr_ceiling_color[1], data->arr_ceiling_color[2], 0xFF), data->mlx_data.img);
	draw_sprite(data, data->moon.f[(int)(data->moon.frame++ / 20) % data->moon.frame_count], &data->moon);
	ft_background(CUB_HEIGHT / 2, ft_pixel(data->arr_floor_color[0], data->arr_floor_color[1], data->arr_floor_color[2], 0xFF), data->mlx_data.img);
	rotate_player(data);
	move_player(data);
	fraction = PI / 3 / CUB_WIDTH;
	ray_angle = data->player.angle - PI / 6;
	i = 0;
	if (DEBUG == 1)
		draw_ray_line(data, data->player.angle, CUB_WIDTH /2);
	else
	{
		while (i < CUB_WIDTH)
		{
			draw_ray_line(data, ray_angle, i++);
			ray_angle += fraction;
		}
	}
	if (DEBUG)
	{
		draw_map(&data->map, &data->mlx_data);
		if (DEBUG == 2)
			draw_cube(data->player.x / 4, data->player.y / 4, 1, 
			0xFF0000FF, &data->mlx_data);
		else if (DEBUG == 1)
			draw_cube(data->player.x, data->player.y, 1, 
				0xFF0000FF, &data->mlx_data);	
	}
}
