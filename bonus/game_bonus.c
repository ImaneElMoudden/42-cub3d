/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 18:05:20 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/12 18:15:41 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	update_player_pos(void)
{
	t_game		*game;
	t_mlx		*mlx;
	t_player	*player;

	game = game_data();
	mlx = &game->mlx;
	player = &game->player;
	if (mlx->keys[KEY_W])
		move(player->dir_x, player->dir_y);
	if (mlx->keys[KEY_S])
		move(-player->dir_x, -player->dir_y);
	if (mlx->keys[KEY_A])
		move(player->dir_y, -player->dir_x);
	if (mlx->keys[KEY_D])
		move(-player->dir_y, player->dir_x);
	if (mlx->keys[KEY_LEFT])
		rotate(-ROT_SPEED * game->time.delta_time);
	if (mlx->keys[KEY_RIGHT])
		rotate(ROT_SPEED * game->time.delta_time);
}

static void	process_mouse(void)
{
	int		center_x;
	int		center_y;
	int		dx;
	t_mouse	*mouse;
	t_mlx	*m;

	mouse = &game_data()->mouse;
	m = &game_data()->mlx;
	center_x = WIDTH / 2;
	center_y = HEIGHT / 2;
	dx = mouse->x - center_x;
	if (dx == 0)
		return ;
	rotate(dx * MOUSE_SENS);
	mlx_mouse_move(m->mlx, m->mlx_win, center_x, center_y);
	mouse->x = center_x;
	mouse->y = center_y;
}

static void	draw_background(t_img *img, int ceiling, int floor)
{
	int	x;
	int	y;

	y = 0;
	while (y < (HEIGHT / 2))
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, ceiling);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, floor);
			x++;
		}
		y++;
	}
}

int	game_loop(void *p)
{
	t_game	*game;
	t_mlx	*m;
	t_input	*in;

	(void)p;
	game = game_data();
	m = &game->mlx;
	in = &game->input;
	handle_frames();
	process_mouse();
	handle_door(&game->map);
	update_player_pos();
	ft_memset(m->img.addr, 0, HEIGHT * m->img.line_len);
	draw_background(&m->img, in->ceiling_color, in->floor_color);
	raycast();
	display_minimap();
	mlx_put_image_to_window(m->mlx, m->mlx_win, m->img.mlx_img, 0, 0);
	return (0);
}
