/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:05:48 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/11 23:01:07 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	exit_allocation(char **split, t_cub3d *data)
{
	ft_free_split(split);
	free(data->file.all_file);
	ft_dprintf(2, "Error\nAllocation failed\n");
	exit(1);
}

void	creat_2darray_2(int i, int count, char **split, t_cub3d *data)
{
	int	start;

	i = 0;
	count = 0;
	while (data->file.all_file[i])
	{
		start = i;
		while (data->file.all_file[i] && data->file.all_file[i] != '\n')
			i++;
		if (i > start)
		{
			split[count] = ft_strndup(data->file.all_file + start, i - start);
			if (!split[count])
				exit_allocation(split, data);
		}
		else
		{
			split[count] = ft_strdup("\n");
			if (!split[count])
				exit_allocation(split, data);
		}
		count++;
		i++;
	}
	split[count] = NULL;
}

char	**create_2darray(t_cub3d *data)
{
	int		i;
	int		count;
	char	**split;

	i = 0;
	count = 0;
	while (data->file.all_file[i])
	{
		count++;
		while (data->file.all_file[i] && data->file.all_file[i] != '\n')
			i++;
		i++;
	}
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
	{
		free(data->file.all_file);
		ft_dprintf(2, "Error\nAllocation failed\n");
		exit(1);
	}
	creat_2darray_2(i, count, split, data);
	return (split);
}
