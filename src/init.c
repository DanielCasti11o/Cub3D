/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:53:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/13 21:21:43 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "The best cub in the world");
	game->img.buffer = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.buffer,
			&game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->map.tex.c = pack_color(game->img.endian, game->infile.c);
	game->map.tex.f = pack_color(game->img.endian, game->infile.f);
}

