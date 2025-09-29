/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:19:23 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/25 10:30:28 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	clean_mlx(void)
{
	t_mlx	*m;

	m = &game_data()->mlx;
	if (m->tex[NORTH].mlx_img)
		mlx_destroy_image(m->mlx, m->tex[NORTH].mlx_img);
	if (m->tex[SOUTH].mlx_img)
		mlx_destroy_image(m->mlx, m->tex[SOUTH].mlx_img);
	if (m->tex[EAST].mlx_img)
		mlx_destroy_image(m->mlx, m->tex[EAST].mlx_img);
	if (m->tex[WEST].mlx_img)
		mlx_destroy_image(m->mlx, m->tex[WEST].mlx_img);
	if (m->tex[CLOSED_DOOR].mlx_img)
		mlx_destroy_image(m->mlx, m->tex[CLOSED_DOOR].mlx_img);
	if (m->img.mlx_img)
		mlx_destroy_image(m->mlx, m->img.mlx_img);
	if (m->mlx_win)
		mlx_destroy_window(m->mlx, m->mlx_win);
	if (m->mlx)
	{
		mlx_destroy_display(m->mlx);
		free(m->mlx);
	}
}

int	clean(void *p)
{
	safe_free();
	clean_mlx();
	close(game_data()->input.input_fd);
	exit((long)p);
}
