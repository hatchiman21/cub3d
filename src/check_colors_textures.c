/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 23:28:46 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 19:05:56 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_colors_rgb_2(t_cub3d *data, t_data_check_colors *check_data,
		int *array_color)
{
	check_data->temp = ft_strtrim(check_data->color[check_data->ij[0]], " ");
	if (!check_data->temp)
	{
		ft_free_split(check_data->color);
		uncomplete_map(data, 0);
	}
	if (ft_strlen(check_data->temp) > 3)
	{
		free(check_data->temp);
		ft_free_split(check_data->color);
		uncomplete_map(data, 1);
	}
	array_color[check_data->ij[1]] = ft_atoi(check_data->temp);
	if (array_color[check_data->ij[1]] < 0
		|| array_color[check_data->ij[1]] > 255)
	{
		free(check_data->temp);
		ft_free_split(check_data->color);
		uncomplete_map(data, 1);
	}
	free(check_data->temp);
	check_data->ij[0]++;
	check_data->ij[1]++;
}

static void	check_colors_rgb(t_cub3d *data, char *color_before_split,
		int *array_color)
{
	t_data_check_colors	check_data;

	check_data.color = ft_split(color_before_split, ',');
	if (!check_data.color)
		uncomplete_map(data, 0);
	if (ft_strlen_matrix(check_data.color) != 3)
	{
		ft_free_split(check_data.color);
		uncomplete_map(data, 1);
	}
	check_data.ij[0] = 0;
	check_data.ij[1] = 0;
	while (check_data.color[check_data.ij[0]])
	{
		check_colors_rgb_2(data, &check_data, array_color);
	}
	ft_free_split(check_data.color);
}

static void	check_files(t_cub3d *data)
{
	int	fd;

	fd = open(data->bearings.ea, O_RDONLY);
	if (fd == -1)
		uncomplete_map(data, 1);
	close(fd);
	fd = open(data->bearings.no, O_RDONLY);
	if (fd == -1)
		uncomplete_map(data, 1);
	close(fd);
	fd = open(data->bearings.so, O_RDONLY);
	if (fd == -1)
		uncomplete_map(data, 1);
	close(fd);
	fd = open(data->bearings.we, O_RDONLY);
	if (fd == -1)
		uncomplete_map(data, 1);
	close(fd);
}

static void	check_comma(t_cub3d *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->floor_color[i])
	{
		if (data->floor_color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		uncomplete_map(data, 1);
	count = 0;
	i = 0;
	while (data->ceiling_color[i])
	{
		if (data->ceiling_color[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		uncomplete_map(data, 1);
}

void	check_bearings_colors(t_cub3d *data)
{
	check_comma(data);
	check_colors_rgb(data, data->floor_color, data->arr_floor_color);
	check_colors_rgb(data, data->ceiling_color, data->arr_ceiling_color);
	free(data->ceiling_color);
	data->ceiling_color = NULL;
	free(data->floor_color);
	data->floor_color = NULL;
	check_files(data);
}
