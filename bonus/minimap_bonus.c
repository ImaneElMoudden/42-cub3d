/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 15:53:43 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/16 09:39:30 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	get_minimap_limits(t_game *game, t_player *player,
	t_minimap *minimap)
{
	minimap->start_x = player->pos_x - minimap->nb_tiles / 2.0;
	minimap->end_x = player->pos_x + minimap->nb_tiles / 2.0;
	minimap->start_y = player->pos_y - minimap->nb_tiles / 2.0;
	minimap->end_y = player->pos_y + minimap->nb_tiles / 2.0;
	if (minimap->start_x < 0)
		minimap->start_x = 0;
	if (minimap->end_x >= game->map.map_width)
		minimap->start_x = game->map.map_width - minimap->nb_tiles;
	if (minimap->start_y < 0)
		minimap->start_y = 0;
	if (minimap->end_y >= game->map.map_height)
		minimap->start_y = game->map.map_height - minimap->nb_tiles;
	minimap->end_x = minimap->start_x + minimap->nb_tiles;
	minimap->end_y = minimap->start_y + minimap->nb_tiles;
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

static void	draw_player_dot(t_game *game, t_minimap *minimap,
	unsigned int color)
{
	int				pixel_x;
	int				pixel_y;

	minimap->y = -PLAYER_SIZE;
	minimap->player_pixel_x = minimap->player_pos_x * TEX_SIZE;
	minimap->player_pixel_y = minimap->player_pos_y * TEX_SIZE;
	while (minimap->y < PLAYER_SIZE)
	{
		minimap->x = -PLAYER_SIZE;
		while (minimap->x < PLAYER_SIZE)
		{
			pixel_x = minimap->player_pixel_x + minimap->x + OFFSET;
			pixel_y = minimap->player_pixel_y + minimap->y + OFFSET;
			put_pixel(&game->mlx.img, pixel_x, pixel_y, color);
			minimap->x++;
		}
		minimap->y++;
	}
}

static void	count_minimap_size(t_game *game, t_minimap *minimap)
{
	minimap->minimap_size = WIDTH / 5;
	if (HEIGHT < minimap->minimap_size)
		minimap->minimap_size = HEIGHT;
	minimap->nb_tiles = minimap->minimap_size / TEX_SIZE;
	if (minimap->nb_tiles > game->map.map_width)
		minimap->nb_tiles = game->map.map_width;
	if (minimap->nb_tiles > game->map.map_height)
		minimap->nb_tiles = game->map.map_height;
	minimap->minimap_size = minimap->nb_tiles * TEX_SIZE;
}

void	display_minimap(void)
{
	t_game			*game;
	t_img			*img;
	t_minimap		*minimap;

	game = game_data();
	minimap = &game->minimap;
	minimap->y = -1;
	img = &game->mlx.img;
	count_minimap_size(game, minimap);
	get_minimap_limits(game, &game->player, minimap);
	while (++(minimap->y) < minimap->minimap_size)
	{
		minimap->x = -1;
		while (++minimap->x < minimap->minimap_size)
		{
			minimap->color = which_color(game, minimap->x, minimap->y);
			put_pixel(&game->mlx.img, minimap->x + OFFSET,
				minimap->y + OFFSET, minimap->color);
		}
	}
	draw_player_dot(game, &game->minimap, 0xFF0000);
	draw_player_dir(game, 0xFF0000);
}
