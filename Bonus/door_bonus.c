/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 21:01:18 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:46 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	handle_door(t_map *map)
{
	t_player	*player;
	float		new_x;
	float		new_y;
	int			nx;
	int			ny;

	if (!game_data()->mlx.keys[KEY_E])
		return ;
	player = &game_data()->player;
	map = &game_data()->map;
	new_x = player->pos_x + player->dir_x * DOOR_DIST;
	new_y = player->pos_y + player->dir_y * DOOR_DIST;
	nx = (int)new_x;
	ny = (int)new_y;
	if (ny < 0 || ny >= map->map_height || nx < 0 || nx >= map->map_width)
		return ;
	if (map->map[ny][nx] == 'd')
		map->map[ny][nx] = 'D';
	else if (map->map[ny][nx] == 'D')
		map->map[ny][nx] = 'd';
}
