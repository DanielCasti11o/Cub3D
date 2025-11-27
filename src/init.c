/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:53:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/27 21:30:06 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	ft_freestr(&game->infile.no);
	if (init_texture(game, &game->map.tex.so, game->infile.so) == 1)
		return (1);
	ft_freestr(&game->infile.so);
	if (init_texture(game, &game->map.tex.we, game->infile.we) == 1)
		return (1);
	ft_freestr(&game->infile.we);
	if (init_texture(game, &game->map.tex.ea, game->infile.ea) == 1)
		return (1);
	ft_freestr(&game->infile.ea);
	return (0);
}

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		return (1);
	game->img.ptr = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img.ptr == NULL)
		return (1);
	game->img.addr = mlx_get_data_addr(game->img.ptr,
			&game->img.bpp,
			&game->img.size_line, &game->endian);
	game->img.width = WIDTH;
	game->img.height = HEIGHT;
	if (init_textures(game) == 1)
		return (1);
	return (0);
}

void	init_events(t_game *game)
{
	game->keys.s = 0;
	game->keys.a = 0;
	game->keys.d = 0;
	game->keys.w = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.up = 0;
	game->keys.down = 0;
	mlx_hook(game->win,
		KeyPress, KeyPressMask,
		ft_key_press,
		game);
	mlx_hook(game->win,
		KeyRelease, KeyReleaseMask,
		ft_key_release,
		game);
	mlx_hook(game->win,
		DestroyNotify, StructureNotifyMask,
		ft_close,
		game);
	mlx_loop_hook(game->mlx,
		ft_events,
		game);
}

int	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img.ptr = NULL;
	game->img.addr = NULL;
	game->map.tex.no.ptr = NULL;
	game->map.tex.no.addr = NULL;
	game->map.tex.so.ptr = NULL;
	game->map.tex.so.addr = NULL;
	game->map.tex.we.ptr = NULL;
	game->map.tex.we.addr = NULL;
	game->map.tex.ea.ptr = NULL;
	game->map.tex.ea.addr = NULL;
	game->frame_count = 0;
	if (init_mlx(game) == 1)
		return (1);
	game->fov_tan = tan(degrees(ANGLE_FOV / 2));
	raycasting(game);
	mini_map(game);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, WIN_TITLE);
	if (game->win == NULL)
		return (1);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	init_events(game);
	mlx_loop(game->mlx);
	return (0);
}
