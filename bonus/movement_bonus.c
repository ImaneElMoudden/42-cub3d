/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:30:16 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 20:13:41 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_collision(int y, int x)
{
	t_map	*map;

	map = &game_data()->map;
	return (y < 0 || y > map->map_height || x < 0 || x > map->map_width
		|| map->map[y][x] == '1' || map->map[y][x] == 'd');
}

void	move_up(void)
{
	t_game		*game;
	t_player	*player;
	double		new_x;
	double		new_y;
	double		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x + player->dir_x * move_speed;
	new_y = player->pos_y + player->dir_y * move_speed;
	if (check_collision((int)new_y, (int)new_x))
		return ;
	player->pos_x = new_x;
	player->pos_y = new_y;
}

void	move_down(void)
{
	t_game		*game;
	t_player	*player;
	double		new_x;
	double		new_y;
	double		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x - player->dir_x * move_speed;
	new_y = player->pos_y - player->dir_y * move_speed;
	if (check_collision((int)new_y, (int)new_x))
		return ;
	player->pos_x = new_x;
	player->pos_y = new_y;
}

void	move_left(void)
{
	t_game		*game;
	t_player	*player;
	double		new_x;
	double		new_y;
	double		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x + player->dir_y * move_speed;
	new_y = player->pos_y - player->dir_x * move_speed;
	if (check_collision((int)new_y, (int)new_x))
		return ;
	player->pos_x = new_x;
	player->pos_y = new_y;
}

void	move_right(void)
{
	t_game		*game;
	t_player	*player;
	double		new_x;
	double		new_y;
	double		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x - player->dir_y * move_speed;
	new_y = player->pos_y + player->dir_x * move_speed;
	if (check_collision((int)new_y, (int)new_x))
		return ;
	player->pos_x = new_x;
	player->pos_y = new_y;
}
