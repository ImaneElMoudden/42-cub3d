/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:46:27 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/09/26 10:39:09 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	handle_key(int key, void *p)
{
	t_mlx	*m;

	(void)p;
	m = &game_data()->mlx;
	if (key == XK_w)
		m->keys[KEY_W] = 1;
	if (key == XK_a)
		m->keys[KEY_A] = 1;
	if (key == XK_s)
		m->keys[KEY_S] = 1;
	if (key == XK_d)
		m->keys[KEY_D] = 1;
	if (key == XK_Left)
		m->keys[KEY_LEFT] = 1;
	if (key == XK_Right)
		m->keys[KEY_RIGHT] = 1;
	if (key == XK_e)
		m->keys[KEY_E] = 1;
	if (key == XK_Escape)
		clean(NULL);
	return (0);
}

int	handle_key_release(int key, void *p)
{
	t_mlx	*m;

	(void)p;
	m = &game_data()->mlx;
	if (key == XK_w)
		m->keys[KEY_W] = 0;
	if (key == XK_a)
		m->keys[KEY_A] = 0;
	if (key == XK_s)
		m->keys[KEY_S] = 0;
	if (key == XK_d)
		m->keys[KEY_D] = 0;
	if (key == XK_Left)
		m->keys[KEY_LEFT] = 0;
	if (key == XK_Right)
		m->keys[KEY_RIGHT] = 0;
	return (0);
}

int	mouse_movement(int x, int y, void *p)
{
	t_mouse	*mouse;

	(void)p;
	mouse = &game_data()->mouse;
	mouse->x = x;
	mouse->y = y;
	return (0);
}
