/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aatieh <aatieh@student.42amman.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 06:27:32 by aatieh            #+#    #+#             */
/*   Updated: 2025/04/15 21:44:41 by aatieh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	determine_init_angle(t_cub3d *data)
{
	if (data->player.c == 'N')
		data->player.angle = 270 * (PI / 180);
	else if (data->player.c == 'S')
		data->player.angle = 90 * (PI / 180);
	else if (data->player.c == 'W')
		data->player.angle = 180 * (PI / 180);
	else if (data->player.c == 'E')
		data->player.angle = 0 * (PI / 180);
}

void	move_player_extend(t_cub3d *data, float step_x, float step_y)
{
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_A)
		&& !touch(data->player.x + step_y, data->player.y - step_x, data))
	{
		data->player.x += SPEED * sin(data->player.angle);
		data->player.y -= SPEED * cos(data->player.angle);
	}
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_D)
		&& !touch(data->player.x - step_y, data->player.y + step_x, data))
	{
		data->player.x -= SPEED * sin(data->player.angle);
		data->player.y += SPEED * cos(data->player.angle);
	}
}

void	move_player(t_cub3d *data)
{
	float	step_x;
	float	step_y;

	step_x = SPEED * COLISION * cos(data->player.angle);
	step_y = SPEED * COLISION * sin(data->player.angle);
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_W)
		&& !touch(data->player.x + step_x, data->player.y + step_y, data))
	{
		data->player.x += SPEED * cos(data->player.angle);
		data->player.y += SPEED * sin(data->player.angle);
	}
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_S)
		&& !touch(data->player.x - step_x, data->player.y - step_y, data))
	{
		data->player.x -= SPEED * cos(data->player.angle);
		data->player.y -= SPEED * sin(data->player.angle);
	}
	else
		move_player_extend(data, step_x, step_y);
}

void	rotate_player(t_cub3d *data)
{
	if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx_data.mlx);
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_LEFT))
		data->player.angle -= ROTATE_SPEED;
	else if (mlx_is_key_down(data->mlx_data.mlx, MLX_KEY_RIGHT))
		data->player.angle += ROTATE_SPEED;
	if (data->player.angle < 0)
		data->player.angle += 2 * PI;
	else if (data->player.angle > 2 * PI)
		data->player.angle -= 2 * PI;
}
