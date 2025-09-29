/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:39:02 by klamachi          #+#    #+#             */
/*   Updated: 2025/09/29 14:14:26 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exit_with_error(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	write(2, "Error\n", 6);
	write(2, msg, len);
	write(2, "\n", 1);
	clean((void *)1);
}

static void	init_main_img(t_mlx *mlx)
{
	t_img	*img;

	img = &mlx->img;
	img->mlx_img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!img->mlx_img)
		exit_with_error("Error: mlx_new_image failed !");
	img->addr = mlx_get_data_addr(img->mlx_img, &img->bpp,
			&img->line_len, &img->endian);
	if (!img->addr)
		exit_with_error("Error: mlx_get_data_addr failed !");
}

static void	load_texture(t_mlx *mlx, int dir, char *path)
{
	mlx->tex[dir].mlx_img = mlx_xpm_file_to_image(mlx->mlx, path,
			&mlx->tex[dir].width, &mlx->tex[dir].height);
	if (!mlx->tex[dir].mlx_img)
		exit_with_error("mlx_xpm_file_to_image failed !");
	mlx->tex[dir].addr = mlx_get_data_addr(mlx->tex[dir].mlx_img,
			&mlx->tex[dir].bpp, &mlx->tex[dir].line_len,
			&mlx->tex[dir].endian);
	if (!mlx->tex[dir].addr)
		exit_with_error("mlx_get_data_addr failed !");
}

static void	init_textures(t_mlx *mlx, t_input *input)
{
	load_texture(mlx, NORTH, input->no_path);
	load_texture(mlx, SOUTH, input->so_path);
	load_texture(mlx, WEST, input->we_path);
	load_texture(mlx, EAST, input->ea_path);
}

void	init_mlx_var(void)
{
	t_game	*game;
	t_mlx	*mlx;

	game = game_data();
	mlx = &game->mlx;
	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		exit_with_error("Error: mlx_init failed !");
	mlx->mlx_win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "CUB3D");
	if (!mlx->mlx_win)
		exit_with_error("Error: mlx_new_window failed !");
	init_main_img(&game->mlx);
	init_textures(&game->mlx, &game->input);
}
