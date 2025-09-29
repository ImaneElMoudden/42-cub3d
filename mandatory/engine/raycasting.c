/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:48:41 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 13:50:37 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	line_length(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwall_dist = ray->sidedist_x - ray->delta_dist_x;
	else
		ray->perpwall_dist = ray->sidedist_y - ray->delta_dist_y;
	if (ray->perpwall_dist < 0.2)
		ray->perpwall_dist = 0.2;
	ray->line_height = HEIGHT / ray->perpwall_dist;
	ray->draw_start = HEIGHT / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = HEIGHT / 2 + ray->line_height / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	ft_delta_dist(t_ray *ray)
{
	ray->delta_dist_x = 1 / fabs(ray->raydir_x);
	if (ray->raydir_x == 0)
		ray->delta_dist_x = INFINITY;
	ray->delta_dist_y = 1 / fabs(ray->raydir_y);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = INFINITY;
}

static void	init_side_dist(t_player *player, t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->sidedist_x = ray->delta_dist_x * (player->pos_x
				- floor(player->pos_x));
		ray->step_x = -1;
	}
	else
	{
		ray->sidedist_x = ray->delta_dist_x
			* (floor(player->pos_x + 1.0) - player->pos_x);
		ray->step_x = 1;
	}
	if (ray->raydir_y < 0)
	{
		ray->sidedist_y = ray->delta_dist_y
			* (player->pos_y - floor(player->pos_y));
		ray->step_y = -1;
	}
	else
	{
		ray->sidedist_y = ray->delta_dist_y
			* (floor(player->pos_y + 1.0) - player->pos_y);
		ray->step_y = 1;
	}
}

static void	dda_loop(t_player *player, t_ray *ray)
{
	int		hit;
	char	**map;

	hit = 0;
	map = game_data()->map.map;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	while (hit != 1)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->side = 0;
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
		}
		else
		{
			ray->side = 1;
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
		}
		if (map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	raycasting(void)
{
	t_ray		*ray;
	t_player	*player;
	t_mlx		*mlx;
	int			x;

	x = 0;
	player = &game_data()->player;
	ray = &game_data()->ray;
	mlx = &game_data()->mlx;
	while (x < WIDTH)
	{
		ray->camera_x = 2.0 * x / WIDTH - 1.0;
		ray->raydir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->raydir_y = player->dir_y + player->plane_y * ray->camera_x;
		ft_delta_dist(ray);
		init_side_dist(player, ray);
		dda_loop(player, ray);
		line_length(ray);
		fr_draw(ray, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.mlx_img, 0, 0);
}
