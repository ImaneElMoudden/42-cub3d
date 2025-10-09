/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:30:22 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 21:53:49 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	main(int ac, char **av)
{
	t_mlx	*m;

	init();
	if (check_input(ac, av) || check_file(av[1]))
		return (clean((void *)1));
	config_game();
	if (init_mlx())
		return (clean((void *)1));
	m = &game_data()->mlx;
	mlx_loop_hook(m->mlx, &game_loop, NULL);
	mlx_hook(m->mlx_win, 2, 1L << 0, handle_key, NULL);
	mlx_hook(m->mlx_win, 3, 1L << 1, handle_key_release, NULL);
	mlx_hook(m->mlx_win, 6, 1L << 6, mouse_movement, NULL);
	mlx_hook(m->mlx_win, 17, 0, clean, NULL);
	mlx_loop(m->mlx);
}
