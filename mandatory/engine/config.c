/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:23:07 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 15:11:42 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_player_dir(t_player *player, t_input *input)
{
	if (input->player_dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
	}
	else if (input->player_dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
	}
	else if (input->player_dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
	}
	else if (input->player_dir == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
	}
}

void	config_game(void)
{
	t_game		*game;
	t_player	*player;
	double		plane_len;
	double		fov_rad;

	fov_rad = FOV * M_PI / 180.0;
	plane_len = tan(fov_rad / 2);
	game = game_data();
	player = &game->player;
	set_player_dir(player, &game->input);
	player->plane_x = -player->dir_y * plane_len;
	player->plane_y = player->dir_x * plane_len;
	game->time.last_time = get_time_in_seconds();
	game->time.target = 1.0 / 60;
}
