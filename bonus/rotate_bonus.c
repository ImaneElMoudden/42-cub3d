/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:05:40 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:46 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	rotate(float angle)
{
	t_player	*p;
	float		old_dir_x;
	float		old_plane_x;
	float		c;
	float		s;

	p = &game_data()->player;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	c = cosf(angle);
	s = sinf(angle);
	p->dir_x = p->dir_x * c - p->dir_y * s;
	p->dir_y = old_dir_x * s + p->dir_y * c;
	p->plane_x = p->plane_x * c - p->plane_y * s;
	p->plane_y = old_plane_x * s + p->plane_y * c;
}

void	rotate_left(void)
{
	t_game	*game;
	float	rot_speed;

	game = game_data();
	rot_speed = BASE_ROT_SPEED * game->time.delta_time;
	rotate(-rot_speed);
}

void	rotate_right(void)
{
	t_game	*game;
	float	rot_speed;

	game = game_data();
	rot_speed = BASE_ROT_SPEED * game->time.delta_time;
	rotate(rot_speed);
}
