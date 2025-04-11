/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 22:08:45 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/11 23:33:04 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_strlen_matrix(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	uncomplete_map(t_cub3d *data, int flag)
{
	if (data->file.split_all_file)
		ft_free_split(data->file.split_all_file);
	if (data->bearings.ea)
		free(data->bearings.ea);
	if (data->bearings.no)
		free(data->bearings.no);
	if (data->bearings.so)
		free(data->bearings.so);
	if (data->bearings.we)
		free(data->bearings.we);
	if (data->file.complete_file)
		free(data->file.complete_file);
	if (data->floor_color)
		free(data->floor_color);
	if (data->ceiling_color)
		free(data->ceiling_color);
	if (flag == 1)
		printf("Error\nWrong map\n");
	else if (flag == 0)
		printf("Error\nMemory allocation faild\n");
	exit(1);
}

char	*ft_strndup(const char *s, int n)
{
	char	*dup;
	char	*d;
	int		len;

	len = 0;
	while (s[len] && len < n)
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	d = dup;
	while (len > 0)
	{
		*d = *s;
		d++;
		s++;
		len--;
	}
	*d = '\0';
	return (dup);
}
