/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:15:10 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/11 10:48:54 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_player_tile(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_tile(char c)
{
	return (is_player_tile(c) || c == '0' || c == '1' || c == ' ');
}

static int	validate_grid(int i, int j, char c, int *count)
{
	t_game	*game;

	game = game_data();
	if (!is_valid_tile(c))
		return (write_error("Map: Invalid map character\n"));
	if (is_player_tile(c))
	{
		(*count)++;
		game->player.pos_x = j + 0.5;
		game->player.pos_y = i + 0.5;
		game->input.player_dir = c;
		game_data()->map.map[i][j] = '0';
	}
	return (0);
}

static int	scan_map(void)
{
	t_map	*map;
	int		player_count;
	int		i;
	int		j;

	map = &game_data()->map;
	player_count = 0;
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (validate_grid(i, j, map->map[i][j], &player_count))
				return (1);
			j++;
		}
		if (map->map_width < j)
			map->map_width = j;
		i++;
	}
	map->map_height = i;
	if (player_count != 1)
		return (write_error("Map: Map must contain one player\n"));
	return (0);
}

int	validate_map(void)
{
	t_map	*map;

	map = &game_data()->map;
	if (!map->map)
		return (write_error("Map: no map in file\n"));
	if (scan_map() || check_map_boundaries())
		return (1);
	return (finalize_map());
}
