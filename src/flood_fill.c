/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:24:52 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/15 19:11:29 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	get_poisition_of_player(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'N' || data->map.map[i][j] == 'S'
				|| data->map.map[i][j] == 'E' || data->map.map[i][j] == 'W')
			{
				data->player.c = data->map.map[i][j];
				data->player.y = i + 0.5;
				data->player.x = j + 0.5;
			}
			j++;
		}
		i++;
	}
}
void	heigh_width(t_cub3d *data)
{
	int i = 0;
	data->map.height = 0;
	data->map.width = 0;
	
	while (data->map.map[i])
	{
		if ((int)ft_strlen(data->map.map[i]) > data->map.width)
			data->map.width = ft_strlen(data->map.map[i]);
		i++;
		data->map.height++;
	}
}

void	flood_fill(t_cub3d *data, int y, int x)
{
	if (y < 0 || x < 0 || y >= data->map.height || x >= data->map.width)
	{
		ft_free_split(data->map.copy_map);
		ft_free_split(data->map.map);
		uncomplete_map(data, 1);
	}
	// if (data->map.copy_map[y][x] == ' ')
	// {
	// 	ft_free_split(data->map.copy_map);
	// 	ft_free_split(data->map.map);
	// 	uncomplete_map(data, 1);
	// }
	if (data->map.copy_map[y][x] == '1' || data->map.copy_map[y][x] == '2')
		return;
	data->map.copy_map[y][x] = '2';
	flood_fill(data, y + 1, x);
	flood_fill(data, y - 1, x);
	flood_fill(data, y, x + 1);
	flood_fill(data, y, x - 1);
}

void	pad_map(t_cub3d *data)
{
	int		y = 0;
	int		max_len = 0;

	while (data->map.copy_map[y])
	{
		int len = ft_strlen(data->map.copy_map[y]);
		if (len > max_len)
			max_len = len;
		y++;
	}
	data->map.width = max_len;
	data->map.height = y;
	y = 0;
	while (data->map.copy_map[y])
	{
		int len = ft_strlen(data->map.copy_map[y]);
		if (len < max_len)
		{
			char *new_line = malloc(max_len + 1);
			if (!new_line)
			{
				ft_free_split(data->map.copy_map);
				uncomplete_map(data, 0);
			}
			ft_memcpy(new_line, data->map.copy_map[y], len);
			ft_memset(new_line + len, ' ', max_len - len);
			new_line[max_len] = '\0';
			free(data->map.copy_map[y]);
			data->map.copy_map[y] = new_line;
		}
		y++;
	}
}

void	check_map_borders(t_cub3d *data)
{
	int	y;
	int	x;
	int	last_char;

	x = 0;
	while (data->map.copy_map[0][x])
	{
		if (data->map.copy_map[0][x] != '1' && data->map.copy_map[0][x] != ' ')
		{
			ft_free_split(data->map.copy_map);
			uncomplete_map(data, 1);
		}
		x++;
	}
	x = 0;
	int last_row = data->map.height - 1;
	while (data->map.copy_map[last_row][x])
	{
		if (data->map.copy_map[last_row][x] != '1' && data->map.copy_map[last_row][x] != ' ')
		{
			ft_free_split(data->map.copy_map);
			uncomplete_map(data, 1);
		}
		x++;
	}
	y = 0;
	while (data->map.copy_map[y])
	{
		if (data->map.copy_map[y][0] != '1' && data->map.copy_map[y][0] != ' ')
		{
			ft_free_split(data->map.copy_map);
			uncomplete_map(data, 1);
		}
		last_char = ft_strlen(data->map.copy_map[y]) - 1;
		if (last_char >= 0 &&
			data->map.copy_map[y][last_char] != '1' &&
			data->map.copy_map[y][last_char] != ' ')
		{
			ft_free_split(data->map.copy_map);
			uncomplete_map(data, 1);
		}
		y++;
	}
}
