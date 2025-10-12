/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:18:30 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/12 17:54:15 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_collision(int y, int x)
{
	t_map	*map;

	map = &game_data()->map;
	return (y < 0 || y > map->map_height || x < 0 || x > map->map_width
		|| map->map[y][x] == '1' || map->map[y][x] == 'd');
}

void	move(double dir_x, double dir_y)
{
	t_player	*player;
	t_time		*time;
	t_map		*map;
	double		nx;
	double		ny;

	player = &game_data()->player;
	time = &game_data()->time;
	map = &game_data()->map;
	nx = player->pos_x + dir_x * MOVE_SPEED * time->delta_time;
	ny = player->pos_y + dir_y * MOVE_SPEED * time->delta_time;
	if (check_collision((int)ny, (int)nx))
		return ;
	player->pos_x = nx;
	player->pos_y = ny;
}

void	rotate(int dir_rot)
{
	t_game		*game;
	t_player	*player;
	double		old_dir_x;
	double		old_plane_x;
	double		angl;

	game = game_data();
	player = &game->player;
	angl = ROT_SPEED * game->time.delta_time * dir_rot;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angl) - player->dir_y * sin(angl);
	player->dir_y = old_dir_x * sin(angl) + player->dir_y * cos(angl);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angl) - player->plane_y * sin(angl);
	player->plane_y = old_plane_x * sin(angl) + player->plane_y * cos(angl);
}

void	actions(void)
{
	t_mlx		*mlx;
	t_player	*player;

	mlx = &game_data()->mlx;
	player = &game_data()->player;
	if (mlx->keys[KEY_W] == 1)
		move(player->dir_x, player->dir_y);
	if (mlx->keys[KEY_S] == 1)
		move(-player->dir_x, -player->dir_y);
	if (mlx->keys[KEY_D] == 1)
		move(-player->dir_y, player->dir_x);
	if (mlx->keys[KEY_A] == 1)
		move(player->dir_y, -player->dir_x);
	if (mlx->keys[KEY_RIGHT] == 1)
		rotate(1);
	if (mlx->keys[KEY_LEFT] == 1)
		rotate(-1);
}
