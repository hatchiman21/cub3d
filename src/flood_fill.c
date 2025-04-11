/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:24:52 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/11 22:58:19 by sbibers          ###   ########.fr       */
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
				data->char_player = data->map.map[i][j];
				data->player_y = i;
				data->player_x = j;
			}
			j++;
		}
		i++;
	}
}

void	flood_fill(t_cub3d *data, int player_y, int player_x)
{
	if (player_y < 0 || player_x < 0 || !data->map.map[player_y])
	{
		ft_free_split(data->map.map);
		uncomplete_map(data, 1);
	}
	if (player_x >= (int)ft_strlen(data->map.map[player_y]))
	{
		ft_free_split(data->map.map);
		uncomplete_map(data, 1);
	}
	if (data->map.map[player_y][player_x] == ' ')
	{
		ft_free_split(data->map.map);
		uncomplete_map(data, 1);
	}
	if (data->map.map[player_y][player_x] == '1'
		|| data->map.map[player_y][player_x] == '2')
		return ;
	data->map.map[player_y][player_x] = '2';
	flood_fill(data, player_y - 1, player_x);
	flood_fill(data, player_y + 1, player_x);
	flood_fill(data, player_y, player_x - 1);
	flood_fill(data, player_y, player_x + 1);
}
