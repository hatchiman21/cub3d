/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:42 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/08 23:28:08 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "../libft/inc/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

typedef struct s_cub3d
{
    char *all_file;
    char **split_all_file;
    char **map;
    char **copy_map;
    char *no;
    char *so;
    char *we;
    char *ea;
    char *floor_color;
    char *ceiling_color;
}   t_cub3d;

char    *read_map(char *map_name);
void     check_empty_read(char *map_name);
void    check_file_name(char *file_name);
char	*ft_strjoin_gnl(char *s1, char *s2);

#endif
