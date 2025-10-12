/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:30:16 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/12 17:55:51 by ielmoudd         ###   ########.fr       */
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

void	move(double dir1, double dir2)
{
	t_game		*game;
	t_player	*player;
	double		nx;
	double		ny;
	double		speed;

	game = game_data();
	player = &game->player;
	speed = MOVE_SPEED * game->time.delta_time;
	nx = player->pos_x + dir1 * speed;
	ny = player->pos_y + dir2 * speed;
	if (check_collision((int)ny, (int)nx))
		return ;
	player->pos_x = nx;
	player->pos_y = ny;
}

void	rotate(double angle)
{
	t_player	*p;
	double		old_dir_x;
	double		old_plane_x;

	p = &game_data()->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}
