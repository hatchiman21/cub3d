/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:42 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/15 19:12:34 by aatieh           ###   ########.fr       */
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

# define PI 3.14159265358979323846
# define SPEED 2
# define ROTATE_SPEED 0.05
# define CUB_WIDTH 1280
# define CUB_HEIGHT 720
# define BLOCK 32
# ifndef DEBUG
#  define DEBUG 2
# endif
# define COLISION 15

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}			t_color;

typedef struct s_texture
{
	mlx_texture_t	*texture;
	int texX;
	double wallX;
	uint32_t color;
	double step;
	double texPos;
	int texY;
}				t_texture;
typedef struct s_ray
{
	int		mapX;
	int		mapY;
	float	sideDistX;
	float	sideDistY;
	float	deltaDistX;
	float	deltaDistY;
	int		stepX;
	int		stepY;
	int		side;
	float	rayDirX;
	float	rayDirY;
}			t_ray;

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

typedef struct s_mlx_cube3d
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_mlx_cube3d;

typedef struct s_player
{
	char	c;
	float	x;
	float	y;
	float	angle;
	double	x_delta;
}			t_player;

typedef struct s_cub3d
{
	t_file			file;
	t_bearings		bearings;
	t_count			counter;
	t_map			map;
	t_player		player;
	t_mlx_cube3d	mlx_data;
	char			*floor_color;
	char			*ceiling_color;
	int				arr_floor_color[3];
	int				arr_ceiling_color[3];
}					t_cub3d;

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

void			determine_init_angle(t_cub3d *data);
void			move_player(t_cub3d *data);
void			move_player_extend(t_cub3d *data);
void			rotate_player(t_cub3d *data);

void			draw_map(t_map *map, t_mlx_cube3d *mlx_data);
void			draw_cube(float x, float y, int size, int color, t_mlx_cube3d *mlx_data);
void			draw_line(float x1, float y1, float x2, float y2, int color, t_mlx_cube3d *mlx_data);

void			my_put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void			clear_image(t_mlx_cube3d *mlx_data);
void			ft_background(uint32_t start, uint32_t color, mlx_image_t *img);
void			handle_drawing(t_mlx_cube3d *mlx_data, t_cub3d *data);

bool			touch(float px, float py, t_cub3d *data);
void			ft_draw_loop(void* param);
void			draw_ray_line(t_cub3d *data, float ray_angle, int i);
void			draw_3d_ray_line(float ray_x, float ray_y, int i, t_cub3d *data);

void	delete_textures(t_cub3d *data);

#endif
