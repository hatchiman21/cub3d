/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 21:19:10 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/19 19:03:26 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void define_line_height(t_vertival_line *ln, t_ray *ray, t_cub3d *data)
{
	if (ray->side == 0)
		ln->distance = (ray->map_x - (data->player.x / BLOCK) + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ln->distance = (ray->map_y - (data->player.y / BLOCK) + (1 - ray->step_y) / 2) / ray->ray_dir_y;
	ln->line_height = (int)(CUB_HEIGHT / ln->distance);
	ln->draw_start = -ln->line_height / 2 + CUB_HEIGHT / 2;
	if (ln->draw_start < 0)
		ln->draw_start = 0;
	ln->draw_end = ln->line_height / 2 + CUB_HEIGHT / 2;
	if (ln->draw_end >= CUB_HEIGHT)
		ln->draw_end = CUB_HEIGHT - 1;
	if (ray->side == 0)
		ln->wall_x = data->player.y / BLOCK + ln->distance * ray->ray_dir_y;
	else
		ln->wall_x = data->player.x / BLOCK + ln->distance * ray->ray_dir_x;
	ln->wall_x -= floor((ln->wall_x));
}

void vertical_line_loop(t_vertival_line *ln, t_cub3d *data, int x)
{
	t_color cr;

	while (ln->draw_start <= ln->draw_end)
	{
		ln->tex_y = (int)ln->tex_pos & (ln->texture->width - 1);
		ln->tex_pos += ln->step;
		if (ln->tex_x < 0)
			ln->tex_x = 0;
		if (ln->tex_x >= (int)ln->texture->width)
			ln->tex_x = (int)ln->texture->width - 1;
		if (ln->tex_y < 0)
			ln->tex_y = 0;
		if (ln->tex_y >= (int)ln->texture->height)
			ln->tex_y = (int)ln->texture->height - 1;
		ln->pixel_index = (ln->tex_y * ln->texture->width + ln->tex_x) * 4;
		cr.r = ln->texture->pixels[ln->pixel_index + 0];
		cr.g = ln->texture->pixels[ln->pixel_index + 1];
		cr.b = ln->texture->pixels[ln->pixel_index + 2];
		cr.a = ln->texture->pixels[ln->pixel_index + 3];
		cr.color = (cr.r << 24) | (cr.g << 16) | (cr.b << 8) | cr.a;
		my_put_pixel(data->mlx_data.img, x, ln->draw_start++, cr.color);
	}
}

void draw_vertical_line(t_ray *ray, t_cub3d *data, int x)
{
	t_vertival_line ln;

	if (ray->map_y >= data->map.height || ray->map_x >= data->map.width)
		return;
	define_line_height(&ln, ray, data);
	if (data->map.map[ray->map_y][ray->map_x] == 'O' && (ln.wall_x >= 0.33 && ln.wall_x <= 0.66))
	{
		perform_dda(ray, data);
		draw_vertical_line(ray, data, x);
		return;
	}
	ln.texture = get_texture(ray, data);
	ln.tex_x = (int)(ln.wall_x * (double)(ln.texture->width));
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ln.tex_x = ln.texture->width - ln.tex_x - 1;
	else if (ray->side == 1 && ray->ray_dir_y < 0)
	{
		ln.tex_x = ln.texture->width - ln.tex_x - 1;
	}
	ln.step = 1.0 * ln.texture->width / ln.line_height;
	ln.tex_pos = (ln.draw_start - (CUB_HEIGHT - ln.line_height) / 2) * ln.step;
	vertical_line_loop(&ln, data, x);
}
