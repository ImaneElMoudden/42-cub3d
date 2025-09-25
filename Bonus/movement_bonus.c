/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:30:16 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:46 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	check_collision(int y, int x)
{
	t_map	*map;

	map = &game_data()->map;
	return (map->map[y][x] != '1' && map->map[y][x] != 'd');
}

void	move_up(void)
{
	t_game		*game;
	t_player	*player;
	float		new_x;
	float		new_y;
	float		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x + player->dir_x * move_speed;
	new_y = player->pos_y + player->dir_y * move_speed;
	if (check_collision(player->pos_y, new_x + MARGIN)
		&& check_collision(player->pos_y, new_x - MARGIN))
		player->pos_x = new_x;
	if (check_collision(new_y + MARGIN, player->pos_x) && check_collision(new_y
			- MARGIN, player->pos_x))
		player->pos_y = new_y;
}

void	move_down(void)
{
	t_game		*game;
	t_player	*player;
	float		new_x;
	float		new_y;
	float		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x - player->dir_x * move_speed;
	new_y = player->pos_y - player->dir_y * move_speed;
	if (check_collision(player->pos_y, new_x + MARGIN)
		&& check_collision(player->pos_y, new_x - MARGIN))
		player->pos_x = new_x;
	if (check_collision(new_y + MARGIN, player->pos_x) && check_collision(new_y
			- MARGIN, player->pos_x))
		player->pos_y = new_y;
}

void	move_left(void)
{
	t_game		*game;
	t_player	*player;
	float		new_x;
	float		new_y;
	float		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x + player->dir_y * move_speed;
	new_y = player->pos_y - player->dir_x * move_speed;
	if (check_collision(player->pos_y, new_x + MARGIN)
		&& check_collision(player->pos_y, new_x - MARGIN))
		player->pos_x = new_x;
	if (check_collision(new_y + MARGIN, player->pos_x) && check_collision(new_y
			- MARGIN, player->pos_x))
		player->pos_y = new_y;
}

void	move_right(void)
{
	t_game		*game;
	t_player	*player;
	float		new_x;
	float		new_y;
	float		move_speed;

	game = game_data();
	player = &game->player;
	move_speed = BASE_MOVE_SPEED * game->time.delta_time;
	new_x = player->pos_x - player->dir_y * move_speed;
	new_y = player->pos_y + player->dir_x * move_speed;
	if (check_collision(player->pos_y, new_x + MARGIN)
		&& check_collision(player->pos_y, new_x - MARGIN))
		player->pos_x = new_x;
	if (check_collision(new_y + MARGIN, player->pos_x) && check_collision(new_y
			- MARGIN, player->pos_x))
		player->pos_y = new_y;
}
