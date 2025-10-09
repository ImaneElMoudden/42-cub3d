/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:04:56 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/09 18:37:46 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	calculate_raydir(int x)
{
	t_game		*game;
	t_ray		*ray;
	t_player	*player;

	game = game_data();
	ray = &game->ray;
	player = &game->player;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->raydir_x = player->dir_x + player->plane_x * ray->camera_x;
	ray->raydir_y = player->dir_y + player->plane_y * ray->camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->raydir_x);
	ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

static void	calculate_sidedist(t_game *game)
{
	if (game->ray.raydir_x < 0)
	{
		game->ray.step_x = -1;
		game->ray.sidedist_x = (game->player.pos_x - game->ray.map_x)
			* game->ray.delta_dist_x;
	}
	else
	{
		game->ray.step_x = 1;
		game->ray.sidedist_x = (game->ray.map_x + 1.0 - game->player.pos_x)
			* game->ray.delta_dist_x;
	}
	if (game->ray.raydir_y < 0)
	{
		game->ray.step_y = -1;
		game->ray.sidedist_y = (game->player.pos_y - game->ray.map_y)
			* game->ray.delta_dist_y;
	}
	else
	{
		game->ray.step_y = 1;
		game->ray.sidedist_y = (game->ray.map_y + 1.0 - game->player.pos_y)
			* game->ray.delta_dist_y;
	}
}

static void	dda_loop(void)
{
	t_game	*game;
	t_ray	*ray;
	t_map	*map;

	game = game_data();
	ray = &game->ray;
	map = &game->map;
	while (1)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map->map[ray->map_y][ray->map_x] == '1'
			|| map->map[ray->map_y][ray->map_x] == 'd')
			break ;
	}
}

static void	calculations(void)
{
	t_game	*game;
	t_ray	*ray;

	game = game_data();
	ray = &game->ray;
	if (ray->side == 0)
		ray->perpwall_dist = ray->sidedist_x - ray->delta_dist_x;
	else
		ray->perpwall_dist = ray->sidedist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perpwall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	raycast(void)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		calculate_raydir(x);
		calculate_sidedist(game_data());
		dda_loop();
		calculations();
		draw(x);
		x++;
	}
}
