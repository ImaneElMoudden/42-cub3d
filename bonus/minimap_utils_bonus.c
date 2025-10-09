/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 15:47:48 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/09 15:47:50 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_player_dir(t_game *game, unsigned int color)
{
	int			len;
	int			i;
	int			x;
	int			y;
	t_minimap	*minimap;

	i = 0;
	len = 10;
	minimap = &game->minimap;
	while (i < len)
	{
		x = minimap->player_pixel_x + OFFSET + game->player.dir_x * i;
		y = minimap->player_pixel_y + OFFSET + game->player.dir_y * i;
		put_pixel(&game->mlx.img, x, y, color);
		i++;
	}
}
