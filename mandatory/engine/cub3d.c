/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:25:43 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:26:19 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = game_data();
	init();
	if (check_input(ac, av) || check_file(av[1]))
		return (clean((void *)1));
	config_game();
	init_mlx_var();
	mlx_hook(game->mlx.mlx_win, 2, 1L << 0, press_handler, game);
	mlx_hook(game->mlx.mlx_win, 3, 1L << 1, release_handler, game);
	mlx_hook(game->mlx.mlx_win, 17, 1L << 0, clean, (void *)1);
	mlx_loop_hook(game->mlx.mlx, ft_render, game);
	mlx_loop(game->mlx.mlx);
	return (0);
}
