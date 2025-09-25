/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:33:34 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:46 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static t_img	*select_imgture(void)
{
	t_game	*game;
	t_img	*tex;
	t_ray	*ray;

	game = game_data();
	ray = &game->ray;
	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			tex = &game->mlx.tex[WEST];
		else
			tex = &game->mlx.tex[EAST];
	}
	else
	{
		if (ray->raydir_y > 0)
			tex = &game->mlx.tex[NORTH];
		else
			tex = &game->mlx.tex[SOUTH];
	}
	if (game->map.map[ray->map_y][ray->map_x] == 'd')
		tex = &game->mlx.tex[CLOSED_DOOR];
	return (tex);
}

static int	get_img_color(t_img *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	calculations(t_game *game, t_img *texture)
{
	t_draw		*draw;
	t_player	*player;
	t_ray		*ray;

	draw = &game_data()->draw;
	player = &game->player;
	ray = &game->ray;
	if (ray->side == 0)
		draw->wall_x = player->pos_y + ray->perpwall_dist * ray->raydir_y;
	else
		draw->wall_x = player->pos_x + ray->perpwall_dist * ray->raydir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (float)texture->width);
	if ((ray->side == 0 && ray->raydir_x > 0) || (ray->side == 1
			&& ray->raydir_y < 0))
		draw->tex_x = texture->width - draw->tex_x - 1;
	draw->step = 1.0f * texture->height / ray->line_height;
	draw->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* draw->step;
}

static void	draw_stripe(int x, t_img *texture)
{
	t_game	*game;
	t_draw	*draw;
	t_ray	*ray;
	int		y;

	game = game_data();
	draw = &game->draw;
	ray = &game->ray;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos & (texture->height - 1);
		draw->tex_pos += draw->step;
		draw->color = get_img_color(texture, draw->tex_x, draw->tex_y);
		put_pixel(&game->mlx.img, x, y, draw->color);
		y++;
	}
}

void	draw(int x)
{
	t_game		*game;
	t_player	*player;
	t_ray		*ray;
	t_img		*texture;
	t_draw		*draw;

	game = game_data();
	draw = &game->draw;
	player = &game->player;
	ray = &game->ray;
	texture = select_imgture();
	calculations(game, texture);
	draw_stripe(x, texture);
}
