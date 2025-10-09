/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:51 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 18:38:26 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_player_dir(char c)
{
	t_game	*game;

	game = game_data();
	if (c == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
	}
	else if (c == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
	}
	else if (c == 'E')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
	}
	else if (c == 'W')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
	}
}

void	config_game(void)
{
	t_player	*player;
	double		fov_rad;
	double		plane_len;

	fov_rad = FOV * M_PI / 180;
	plane_len = tan(fov_rad / 2);
	player = &game_data()->player;
	update_player_dir(game_data()->input.player_dir);
	player->plane_x = -player->dir_y * plane_len;
	player->plane_y = player->dir_x * plane_len;
	game_data()->time.last_time = get_time_in_seconds();
	game_data()->time.target = 1.0 / 60.0;
}
