/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:42 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/09 18:53:48 by sbibers          ###   ########.fr       */
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

typedef struct s_file
{
    char *all_file;
    char **split_all_file;
}  t_file;

typedef struct s_bearings
{
    char *no;
    char *so;
    char *we;
    char *ea;
}   t_bearings;

typedef struct s_map
{
    char **map;
    char **copy_map;
}   t_map;

typedef struct s_cub3d
{
    t_file file;
    t_bearings bearings;
    char *floor_color;
    char *ceiling_color;
}   t_cub3d;

char    *read_map(char *map_name);
void     check_empty_read(char *map_name);
void    check_file_name(char *file_name);
char	*ft_strjoin_gnl(char *s1, char *s2);
void    parse_map(t_cub3d *data);

#endif
