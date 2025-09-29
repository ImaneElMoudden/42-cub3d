/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:35:18 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:36:19 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	press_handler(int key_code, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key_code == 119)
		game->mlx.keys[KEY_W] = 1;
	if (key_code == 97)
		game->mlx.keys[KEY_A] = 1;
	if (key_code == 115)
		game->mlx.keys[KEY_S] = 1;
	if (key_code == 100)
		game->mlx.keys[KEY_D] = 1;
	if (key_code == 65361)
		game->mlx.keys[KEY_LEFT] = 1;
	if (key_code == 65363)
		game->mlx.keys[KEY_RIGHT] = 1;
	if (key_code == 65307)
		clean((void *)1);
	return (0);
}

int	release_handler(int key_code, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key_code == 119)
		game->mlx.keys[KEY_W] = 0;
	if (key_code == 97)
		game->mlx.keys[KEY_A] = 0;
	if (key_code == 115)
		game->mlx.keys[KEY_S] = 0;
	if (key_code == 100)
		game->mlx.keys[KEY_D] = 0;
	if (key_code == 65361)
		game->mlx.keys[KEY_LEFT] = 0;
	if (key_code == 65363)
		game->mlx.keys[KEY_RIGHT] = 0;
	return (0);
}

int	ft_render(void *param)
{
	(void)param;
	frames_handler();
	actions();
	raycasting();
	return (0);
}
