/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 17:58:41 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/08 21:39:18 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include "../MLX42/include/MLX42/MLX42.h"

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;
static mlx_image_t* image2;

// -----------------------------------------------------------------------------

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void ft_randomize(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image->width; ++i)
	{
		for (uint32_t y = 0; y < image->height; ++y)
		{
			uint32_t color = ft_pixel(
				0, // R
				0, // G
				rand() % 0xFF, // B
				0xFF  // A
			);
			mlx_put_pixel(image, i, y, color);
		}
	}
}

void ft_block(void* param)
{
	(void)param;
	for (uint32_t i = 0; i < image2->width; ++i)
	{
		for (uint32_t y = 0; y < image2->height; ++y)
		{
			uint32_t color = ft_pixel(
				0xFF, // R
				0, // G
				0, // B
				0xFF  // A
			);
			mlx_put_pixel(image2, i, y, color);
		}
	}
}

void ft_hook(void* param)
{
	t_cub3d* data = param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->player.y -= 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->player.y += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.x -= 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.x += 1;
}

// -----------------------------------------------------------------------------

// int32_t main(void)
// {
// 	mlx_t* mlx;

// 	// Gotta error check this stuff
// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	image2 = mlx_new_image(mlx, 128, 128);
// 	mlx_image_to_window(mlx, image2, 0, 0);
// 	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	mlx_loop_hook(mlx, ft_block, mlx);
// 	mlx_loop_hook(mlx, ft_randomize, mlx);
// 	mlx_loop_hook(mlx, ft_hook, mlx);
	
// 	mlx_loop(mlx);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }

void	inti_cup_struct(t_cub3d *data)
{
	data->map = ft_split("11111111\n1P000001\n10000001\n11111111", '\n');
	data->copy_map = NULL;
	data->no = ft_strdup("./istockphoto-684133544-612x612.png");
	data->so = NULL;
	data->we = NULL;
	data->ea = NULL;
	data->mlx = mlx_init(1920, 1080, "main", true);
	float zoom_h = 3.5;
	float zoom_w = 1;
	mlx_texture_t* texture = mlx_load_png(data->no); 
	data->image = mlx_new_image(data->mlx, texture->width * zoom_w, texture->height * zoom_h);
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
					mlx_put_pixel(data->image, x * zoom_w + dx, y * zoom_h + dy, color);
				}
			}
		}
	}
	data->player.x = 1;
	data->player.y = 1;
	data->player.angle = 90 * (PI / 180);
	if (!data->mlx || !data->image)
		ft_putstr_fd("error\n", 2);
}

void	calc_zoom(float x, float y, float angle, char **map)
{
	int	x_inc;
	int	y_inc;

	x_inc = 0;
	y_inc = 0;
	while (1)
	{
		`
	}
}

void	free_cub_struct(t_cub3d *data)
{
	if (data->map)
		free_split(data->map, -1);
	if (data->copy_map)
		free_split(data->copy_map, -1);
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->mlx && data->image)
		mlx_delete_image(data->mlx, data->image);
	if (data->mlx)
		mlx_terminate(data->mlx);
}

void	handle_mlx(t_cub3d *data)
{
	// memset(data->image->pixels, 255, data->image->width * data->image->height * sizeof(int32_t));
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	mlx_loop(data->mlx);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);
}

int	main()
{
	t_cub3d	data;

	inti_cup_struct(&data);
	handle_mlx(&data);
	free_cub_struct(&data);
	return (0);    
}
