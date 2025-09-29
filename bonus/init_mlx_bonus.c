/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 20:22:33 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/28 09:22:48 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static int	init_img_buffer(void)
{
	t_mlx	*m;

	m = &game_data()->mlx;
	m->img.mlx_img = mlx_new_image(m->mlx, WIDTH, HEIGHT);
	m->img.addr = mlx_get_data_addr(m->img.mlx_img, &m->img.bpp,
			&m->img.line_len, &m->img.endian);
	m->img.width = WIDTH;
	m->img.height = HEIGHT;
	if (!m->img.mlx_img || !m->img.addr)
		return (write_error("Mlx: image buffer error\n"));
	return (0);
}

static int	get_data_address(void)
{
	t_mlx	*m;

	m = &game_data()->mlx;
	m->tex[NORTH].addr = mlx_get_data_addr(m->tex[NORTH].mlx_img,
			&m->tex[NORTH].bpp, &m->tex[NORTH].line_len, &m->tex[NORTH].endian);
	m->tex[SOUTH].addr = mlx_get_data_addr(m->tex[SOUTH].mlx_img,
			&m->tex[SOUTH].bpp, &m->tex[SOUTH].line_len, &m->tex[SOUTH].endian);
	m->tex[EAST].addr = mlx_get_data_addr(m->tex[EAST].mlx_img,
			&m->tex[EAST].bpp, &m->tex[EAST].line_len, &m->tex[EAST].endian);
	m->tex[WEST].addr = mlx_get_data_addr(m->tex[WEST].mlx_img,
			&m->tex[WEST].bpp, &m->tex[WEST].line_len, &m->tex[WEST].endian);
	m->tex[CLOSED_DOOR].addr = mlx_get_data_addr(m->tex[CLOSED_DOOR].mlx_img,
			&m->tex[CLOSED_DOOR].bpp, &m->tex[CLOSED_DOOR].line_len,
			&m->tex[CLOSED_DOOR].endian);
	if (!m->tex[NORTH].addr || !m->tex[SOUTH].addr || !m->tex[EAST].addr
		|| !m->tex[WEST].addr || !m->tex[CLOSED_DOOR].addr)
		return (write_error("Mlx: mlx_get_data_addr error\n"));
	return (0);
}

static int	init_xpm(void)
{
	t_mlx	*m;
	t_input	*in;

	in = &game_data()->input;
	m = &game_data()->mlx;
	m->tex[NORTH].mlx_img = mlx_xpm_file_to_image(m->mlx, in->no_path,
			&m->tex[NORTH].width, &m->tex[NORTH].height);
	m->tex[SOUTH].mlx_img = mlx_xpm_file_to_image(m->mlx, in->so_path,
			&m->tex[SOUTH].width, &m->tex[SOUTH].height);
	m->tex[EAST].mlx_img = mlx_xpm_file_to_image(m->mlx, in->ea_path,
			&m->tex[EAST].width, &m->tex[EAST].height);
	m->tex[WEST].mlx_img = mlx_xpm_file_to_image(m->mlx, in->we_path,
			&m->tex[WEST].width, &m->tex[WEST].height);
	m->tex[CLOSED_DOOR].mlx_img = mlx_xpm_file_to_image(m->mlx,
			"textures/closed_door.xpm", &m->tex[CLOSED_DOOR].width,
			&m->tex[CLOSED_DOOR].height);
	if (!m->tex[NORTH].mlx_img || !m->tex[SOUTH].mlx_img
		|| !m->tex[EAST].mlx_img || !m->tex[WEST].mlx_img
		|| !m->tex[CLOSED_DOOR].mlx_img)
		return (write_error("Mlx: Unable to load textures\n"));
	return (0);
}

int	init_mlx(void)
{
	t_mlx	*m;
	t_mouse	*mouse;

	m = &game_data()->mlx;
	mouse = &game_data()->mouse;
	m->mlx = mlx_init();
	if (!m->mlx)
		return (write_error("Mlx: mlx_init error\n"));
	m->mlx_win = mlx_new_window(m->mlx, WIDTH, HEIGHT, "cub3D");
	if (!m->mlx_win)
		return (write_error("Mlx: mlx_win error\n"));
	if (init_xpm() || get_data_address() || init_img_buffer())
		return (1);
	mouse->x = WIDTH / 2;
	mouse->y = HEIGHT / 2;
	mlx_mouse_move(m->mlx, m->mlx_win, mouse->x, mouse->y);
	return (0);
}
