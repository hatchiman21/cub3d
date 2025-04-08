/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 22:55:42 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/08 21:00:39 by aatieh           ###   ########.fr       */
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

#define PI 3.14159265358979323846

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
}			t_player;

typedef struct s_cub3d
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	char		**map;
	char		**copy_map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*floor_color;
	char		*ceiling_color;
	t_player	player;
}				t_cub3d;

char	*ft_merge(char *s1, char *s2, int free_s1, int free_s2);

#endif
