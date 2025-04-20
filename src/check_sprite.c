/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:59:43 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/20 18:10:09 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	save_position_of_sprite(t_cub3d *data)
{
	int	ij[2];

	data->count_sprite = 0;
	ij[0] = -1;
	while (data->map.map[++ij[0]])
	{
		ij[1] = -1;
		while (data->map.map[ij[0]][++ij[1]])
		{
			if (data->map.map[ij[0]][ij[1]] == 'B')
			{
				if (data->count_sprite < 1024)
				{
					data->sprite_b[data->count_sprite].y = ij[0];
					data->sprite_b[data->count_sprite].x = ij[1];
					data->count_sprite++;
				}
				else
					break ;
			}
		}
	}
}

void	check_sprite(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->map.map[i][j] == 'B')
			{
				save_position_of_sprite(data);
			}
			j++;
		}
		i++;
	}
}
