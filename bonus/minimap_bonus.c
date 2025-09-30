/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:43 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/30 16:05:22 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	get_minimap_limits(t_game *game, t_player *player, int nb_tiles)
{
	t_minimap	*minimap;

	minimap = &game->minimap;
	minimap->start_x = player->pos_x - nb_tiles / 2.0;
	minimap->end_x = player->pos_x + nb_tiles / 2.0;
	minimap->start_y = player->pos_y - nb_tiles / 2.0;
	minimap->end_y = player->pos_y + nb_tiles / 2.0;
	if (minimap->start_x < 0)
		minimap->start_x = 0;
	if (minimap->end_x >= game->map.map_width)
		minimap->start_x = game->map.map_width - nb_tiles;
	if (minimap->start_y < 0)
		minimap->start_y = 0;
	if (minimap->end_y >= game->map.map_height)
		minimap->start_y = game->map.map_height - nb_tiles;
	minimap->end_x = minimap->start_x + nb_tiles;
	minimap->end_y = minimap->start_y + nb_tiles;
	minimap->player_pos_x = player->pos_x - minimap->start_x;
	minimap->player_pos_y = player->pos_y - minimap->start_y;
}

static unsigned int	which_color(t_game *game, int x, int y)
{
	int	map_x;
	int	map_y;

	map_x = (game->minimap.start_x + (double)x / TEX_SIZE);
	map_y = (game->minimap.start_y + (double)y / TEX_SIZE);
	if (game->map.map[map_y][map_x] == '0')
		return (0x000000);
	if (game->map.map[map_y][map_x] == '1')
		return (0x808080);
	if (game->map.map[map_y][map_x] == 'd')
		return (0x8B4513);
	if (game->map.map[map_y][map_x] == 'D')
		return (0xFFFF00);
	return (0);
}

static void	draw_player_dot(t_game *game, t_minimap *minimap, int color)
{
	int				pixel_x;
	int				pixel_y;
	t_minimap_var	var;

	var.y = -VIEW_RADIUS;
	var.minimap_x = minimap->player_pos_x * TEX_SIZE;
	var.minimap_y = minimap->player_pos_y * TEX_SIZE;
	while (var.y < VIEW_RADIUS)
	{
		var.x = -VIEW_RADIUS;
		while (var.x < VIEW_RADIUS)
		{
			pixel_x = var.minimap_x + var.x + OFFSET;
			pixel_y = var.minimap_y + var.y + OFFSET;
			if (sqrt(var.x * var.x + var.y * var.y) < VIEW_RADIUS)
				put_pixel(&game->mlx.img, pixel_x, pixel_y, color);
			var.x++;
		}
		var.y++;
	}
}

static void	count_minimap_size(t_game *game, int *minimap_size, int *nb_tiles)
{
	*minimap_size = WIDTH / 5;
	if (HEIGHT < *minimap_size)
		*minimap_size = HEIGHT;
	*nb_tiles = *minimap_size / TEX_SIZE;
	if (*nb_tiles > game->map.map_width)
		*nb_tiles = game->map.map_width;
	if (*nb_tiles > game->map.map_height)
		*nb_tiles = game->map.map_height;
	*minimap_size = *nb_tiles * TEX_SIZE;
}

void	display_minimap(void)
{
	t_game			*game;
	t_img			*img;
	t_minimap_var	var;

	var.y = -1;
	game = game_data();
	img = &game->mlx.img;
	count_minimap_size(game, &var.minimap_size, &var.nb_tiles);
	get_minimap_limits(game, &game->player, var.nb_tiles);
	while (++var.y < var.minimap_size)
	{
		var.x = -1;
		while (++var.x < var.minimap_size)
		{
			var.color = which_color(game, var.x, var.y);
			put_pixel(&game->mlx.img, var.x + OFFSET,
				var.y + OFFSET, var.color);
		}
	}
	draw_player_dot(game, &game->minimap, 0xFF0000);
}
