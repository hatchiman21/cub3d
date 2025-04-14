/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:16:00 by sbibers           #+#    #+#             */
/*   Updated: 2025/04/14 14:16:06 by sbibers          ###   ########.fr       */
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
