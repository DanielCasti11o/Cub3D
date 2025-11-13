/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:53:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/13 18:19:08 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "The best cub in the world");
	game->img_w.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img_w.addr = mlx_get_data_addr(game->img_w.img,
			&game->img_w.bits_per_pixel,
			&game->img_w.line_length, &game->img_w.endian);
	game->textures.c = pack_color(game->img_w.endian, game->infile.c);
	game->textures.f = pack_color(game->img_w.endian, game->infile.f);
}

