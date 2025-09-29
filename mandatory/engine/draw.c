/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:26:31 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:33:53 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static t_img	*which_img(t_ray *ray)
{
	t_mlx	*mlx;

	mlx = &game_data()->mlx;
	if (ray->side == 0)
	{
		if (ray->raydir_x < 0)
			return (&mlx->tex[WEST]);
		return (&mlx->tex[EAST]);
	}
	if (ray->raydir_y < 0)
		return (&mlx->tex[NORTH]);
	return (&mlx->tex[SOUTH]);
}

static void	draw_walls(t_game *game, t_ray *ray, int x, int y)
{
	t_img			*texture;
	t_draw			*draw;
	unsigned int	*pixel_addr;

	texture = which_img(ray);
	draw = &game->draw;
	draw->step = (double)texture->height / (double)ray->line_height;
	if (ray->side == 0)
		draw->wall_x = game->player.pos_y + ray->perpwall_dist * ray->raydir_y;
	else
		draw->wall_x = game->player.pos_x + ray->perpwall_dist * ray->raydir_x;
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = texture->width * draw->wall_x;
	draw->tex_pos = (ray->draw_start + ray->line_height / 2.0 - HEIGHT / 2.0)
		* draw->step;
	while (y < ray->draw_end)
	{
		draw->tex_y = floor(draw->tex_pos);
		draw->tex_pos += draw->step;
		pixel_addr = (unsigned int *)(texture->addr + draw->tex_y
				* texture->line_len + draw->tex_x * (texture->bpp / 8));
		put_pixel(&game->mlx.img, x, y, *pixel_addr);
		y++;
	}
}

void	fr_draw(t_ray *ray, int x)
{
	int		y;
	t_game	*game;
	t_img	*img;

	y = 0;
	game = game_data();
	img = &game->mlx.img;
	while (y++ < ray->draw_start)
		put_pixel(img, x, y, game->input.ceiling_color);
	draw_walls(game, ray, x, y);
	y = ray->draw_end;
	while (y++ < HEIGHT)
		put_pixel(img, x, y, game->input.floor_color);
}
