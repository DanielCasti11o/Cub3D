/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:53:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/17 19:52:22 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_game *game)
{
	if (game->infile.no)
		ft_freestr(&game->infile.no);
	if (game->infile.so)
		ft_freestr(&game->infile.so);
	if (game->infile.we)
		ft_freestr(&game->infile.we);
	if (game->infile.ea)
		ft_freestr(&game->infile.ea);
	if (game->map.tex.no.ptr)
		mlx_destroy_image(game->mlx, game->map.tex.no.ptr);
	if (game->map.tex.so.ptr)
		mlx_destroy_image(game->mlx, game->map.tex.so.ptr);
	if (game->map.tex.we.ptr)
		mlx_destroy_image(game->mlx, game->map.tex.we.ptr);
	if (game->map.tex.ea.ptr)
		mlx_destroy_image(game->mlx, game->map.tex.ea.ptr);
	game->map.tex.no.ptr = NULL;
	game->map.tex.so.ptr = NULL;
	game->map.tex.we.ptr = NULL;
	game->map.tex.ea.ptr = NULL;
}

static int	init_texture(t_game *game, t_buf *texture, char *path)
{
	texture->ptr = mlx_xpm_file_to_image(game->mlx,
			path,
			&texture->width,
			&texture->height);
	if (!texture->ptr)
		return (perror_texture(path));
	texture->addr = mlx_get_data_addr(texture->ptr,
			&texture->bpp,
			&texture->size_line,
			&game->endian);
	return (0);
}

static int	init_textures(t_game *game)
{
	game->map.tex.c = pack_color(game->endian, game->infile.c);
	game->map.tex.f = pack_color(game->endian, game->infile.f);
	if (init_texture(game, &game->map.tex.no, game->infile.no) == 1)
		return (1);
	if (init_texture(game, &game->map.tex.so, game->infile.so) == 1)
		return (1);
	if (init_texture(game, &game->map.tex.we, game->infile.we) == 1)
		return (1);
	if (init_texture(game, &game->map.tex.ea, game->infile.ea) == 1)
		return (1);
	return (0);
}

int	init_window(t_game *game)
{
	// TODO: verify errors on each mlx function
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "The best cub in the world");
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp,
			&game->img.size_line, &game->endian);
	game->img.width = WIDTH;
	game->img.height = HEIGHT;
	if (init_textures(game) == 1)
		return (free_textures(game), 1); // TODO: close window and mlx
	return (0);
}

int	init_game(t_game *game)
{
	game->keys.s = 0;
	game->keys.a = 0;
	game->fov_tan = tan(degrees(ANGLE_FOV / 2));
	game->mlx = NULL;
	game->win = NULL;
	game->img.ptr = NULL;
	game->map.tex.no.ptr = NULL;
	game->map.tex.so.ptr = NULL;
	game->map.tex.we.ptr = NULL;
	game->map.tex.ea.ptr = NULL;
	return (init_window(game));
}

