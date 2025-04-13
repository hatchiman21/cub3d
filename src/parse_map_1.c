/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:12:06 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/13 22:46:16 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	ft_newline(char *str, int *i)
{
	while (str[*i] && str[*i] != '\n')
		(*i)++;
	return (*i);
}

void	check_complete_file(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->file.complete_file[i])
	{
		if (data->file.complete_file[i] != '0'
			&& data->file.complete_file[i] != '1'
			&& data->file.complete_file[i] != ' '
			&& data->file.complete_file[i] != '\n'
			&& data->file.complete_file[i] != 'N'
			&& data->file.complete_file[i] != 'S'
			&& data->file.complete_file[i] != 'E'
			&& data->file.complete_file[i] != 'W')
			uncomplete_map(data, 1);
		i++;
	}
	free(data->file.complete_file);
	data->file.complete_file = NULL;
}

void	convert_char_player(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		j = 0;
		while (data->map.map[i][j])
		{
			if (data->player.y == i && data->player.x == j)
				data->map.map[i][j] = 'P';
			j++;
		}
		i++;
	}
}

void	parse_map(t_cub3d *data)
{
	data->file.split_all_file = create_2darray(data);
	free(data->file.all_file);
	data->file.all_file = NULL;
	if (!data->file.split_all_file || !data->file.split_all_file[0])
	{
		ft_dprintf(2, "Error\nFailed to allocate split lines\n");
		exit(1);
	}
	trim_config_lines(data->file.split_all_file);
	split_lines(data);
	check_complete_file(data);
	create_map(data);
	check_map(data);
	check_map_2(data);
	get_poisition_of_player(data);
	data->map.copy_map = ft_dup_matrix(data->map.map, ft_strlen_matrix(data->map.map), 0);
	pad_map(data);
	check_map_borders(data);
	flood_fill(data, data->player.y, data->player.x);
	ft_free_split(data->map.copy_map);
	convert_char_player(data);
}
