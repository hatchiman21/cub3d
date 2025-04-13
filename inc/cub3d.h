/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbibers <sbibers@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:42 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/13 20:10:13 by sbibers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/inc/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data_normalize
{
	char		*key;
	char		*value;
	char		*joined;
	char		*final;
	char		*tmp_key;
	char		*tmp_value;
}				t_data_normalize;

typedef struct s_data_check_colors
{
	char		**color;
	char		*temp;
	int			ij[2];
}				t_data_check_colors;

typedef struct s_file
{
	char		*all_file;
	char		**split_all_file;
	char		*complete_file;
}				t_file;

typedef struct s_bearings
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
}				t_bearings;

typedef struct s_count
{
	int			count_no;
	int			count_so;
	int			count_we;
	int			count_ea;
	int			count_floor_color;
	int			count_ceiling_color;
}				t_count;

typedef struct s_map
{
	char		**map;
	char		**copy_map;
	int			height;
	int			width;
}				t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}			t_player;

typedef struct s_cub3d
{
	t_file		file;
	t_bearings	bearings;
	t_count		counter;
	t_map		map;
	t_player	angle_player;
	char		*floor_color;
	char		*ceiling_color;
	int			arr_floor_color[3];
	int			arr_ceiling_color[3];
	int			player_x;
	int			player_y;
	char		char_player;
}				t_cub3d;

int				skip_spaces(char *str);
int				ft_strlen_matrix(char **str);
char			*read_map(char *map_name);
void			check_empty_read(char *map_name);
void			check_file_name(char *file_name);
char			*ft_strjoin_gnl(char *s1, char *s2);
void			parse_map(t_cub3d *data);
char			**create_2darray(t_cub3d *data);
void			ft_free_split(char **arr);
char			*ft_strndup(const char *s, int n);
void			uncomplete_map(t_cub3d *data, int flag);
void			trim_config_lines(char **lines);
void			split_lines(t_cub3d *data);
void			create_map(t_cub3d *data);
void			check_map(t_cub3d *data);
void			get_poisition_of_player(t_cub3d *data);
void			flood_fill(t_cub3d *data, int player_y, int player_x);
void			check_bearings_colors(t_cub3d *data);
void			check_map_2(t_cub3d *data);
void			stop_create_map(t_cub3d *data);
void			check_map_borders(t_cub3d *data);
void			pad_map(t_cub3d *data);
char			**ft_dup_matrix(char **m, int size, int flag);

#endif
