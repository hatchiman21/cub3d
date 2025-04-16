/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:16:00 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/16 14:13:31 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	**ft_dup_matrix(char **m, int size, int flag)
{
	char	**str;
	int		i;
	int		n;

	n = ft_strlen_matrix(m);
	str = malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
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

void	init_data(t_cub3d *data)
{
	data->map.map = NULL;
	data->file.complete_file = NULL;
	data->floor_color = NULL;
	data->ceiling_color = NULL;
	data->bearings.ea = NULL;
	data->bearings.no = NULL;
	data->bearings.so = NULL;
	data->bearings.we = NULL;
	data->counter.count_ea = 0;
	data->counter.count_no = 0;
	data->counter.count_so = 0;
	data->counter.count_we = 0;
	data->counter.count_floor_color = 0;
	data->counter.count_ceiling_color = 0;
}
