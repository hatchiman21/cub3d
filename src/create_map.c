/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:21:13 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/12 19:27:24 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	stop_create_map(t_cub3d *data)
{
	ft_free_split(data->map.map);
	uncomplete_map(data, 1);
}

void	check_map_2(t_cub3d *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map.map[i])
	{
		if (!skip_spaces(data->map.map[i]))
		{
			j = 0;
			while (data->map.map[i][j] && data->map.map[i][j] == ' ')
				j++;
			if (data->map.map[i][j] == '\n')
				stop_create_map(data);
		}
		i++;
	}
}

void	check_map(t_cub3d *data)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	i = -1;
	player_count = 0;
	while (data->map.map[++i])
	{
		j = -1;
		while (data->map.map[i][++j])
		{
			c = data->map.map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			else if (c != '0' && c != '1' && c != ' ' && c != '\n')
				stop_create_map(data);
		}
	}
	if (player_count != 1)
		stop_create_map(data);
}

void	create_map_2(t_cub3d *data, int *i, int *j)
{
	while (data->file.split_all_file[*i])
	{
		data->map.map[*j] = ft_strdup(data->file.split_all_file[*i]);
		if (!data->map.map[*j])
		{
			ft_free_split(data->map.map);
			uncomplete_map(data, 0);
		}
		(*i)++;
		(*j)++;
	}
	data->map.map[*j] = NULL;
	ft_free_split(data->file.split_all_file);
	data->file.split_all_file = NULL;
}

void	create_map(t_cub3d *data)
{
	int	i;
	int	j;
	int	map_lines;
	int	temp;

	i = 0;
	j = 0;
	map_lines = 0;
	while (data->file.split_all_file[i])
	{
		if (skip_spaces(data->file.split_all_file[i]))
			break ;
		i++;
	}
	temp = i;
	while (data->file.split_all_file[temp])
	{
		map_lines++;
		temp++;
	}
	data->map.map = malloc(sizeof(char *) * (map_lines + 1));
	if (!data->map.map)
		uncomplete_map(data, 0);
	create_map_2(data, &i, &j);
}
