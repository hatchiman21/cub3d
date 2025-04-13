/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:21:13 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/13 20:05:34 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	find_last_line(char **map)
{
	int	i;
	int	j;
	int	empty_lines;

	i = 0;
	while (map[i])
		i++;
	empty_lines = --i;
	while (i >= 0)
	{
		j = 0;
		while (map[i][j] && map[i][j] == ' ')
			j++;
		if (map[i][j] != '\n')
			return (empty_lines);
		empty_lines--;
		i--;
	}
	return (empty_lines);
}

char	**ft_dup_matrix(char **m, int size, int flag)
{
	char	**str;
	int		n;
	int		i;

	i = 0;
	n = ft_strlen_matrix(m);
	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	while (m[i] && i < size)
	{
		str[i] = ft_strdup(m[i]);
		if (!str[i])
		{
			ft_free_split(str);
			return (NULL);
		}
		i++;
	}
	if (flag == 1)
		ft_free_split(m);
	str[i] = NULL;
	return (str);
}

void	free_empty_last_lines(t_cub3d *data)
{
	int	i;
	int	j;
	int	empty_lines;

	i = 0;
	while (data->map.map[i])
		i++;
	empty_lines =  --i;
	while (i >= 0)
	{
		j = 0;
		while (data->map.map[i][j] && data->map.map[i][j] == ' ')
			j++;
		if (data->map.map[i][j] != '\n')
			break;
		empty_lines--;
		i--;
	}
	data->map.map = ft_dup_matrix(data->map.map, empty_lines + 1, 1);
}

void	check_map_2(t_cub3d *data)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = find_last_line(data->map.map);
	while (data->map.map[i] && i <= size)
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
	free_empty_last_lines(data);
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
