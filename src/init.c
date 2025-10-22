/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:53:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/22 20:20:48 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	preinit_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img = NULL;
	game->pos.x = 0;
	game->pos.y = 0;
	game->pos.to_x = 0;
	game->pos.to_y = 0;
	game->pos.ray_x = 0;
	game->pos.ray_y = 0;
	game->pos.is_inside = 0;
	game->pos.value = 0;
	game->vision.triangle = 0;
	game->vision.sphere_inside = 0;
	game->vision.angle = 0;
	game->textures.wall = NULL;
	game->textures.flood = NULL;
	game->textures.door = NULL;
	game->textures.flash = NULL;
	game->textures.sphere = NULL;
	game->textures.mini_map = NULL;
	game->keys.up = 0;
	game->keys.down = 0;
	game->keys.left = 0;
	game->keys.right = 0;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->parse.f = color_rgba(0, 0, 0, 0);
	game->parse.c = color_rgba(0, 0, 0, 0);
	game->parse.no = NULL;
	game->parse.so = NULL;
	game->parse.we = NULL;
	game->parse.ea = NULL;
}

void	init_window(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
}
