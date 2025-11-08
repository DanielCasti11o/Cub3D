/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/08 15:43:56 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray(t_game *game, t_vec dir)
{
	game->pos.ray.x = dir.start.x;
	game->pos.ray.y = dir.start.y;
	while (1)
	{
		game->pos.ray.x += dir.end.x * 0.1;
		game->pos.ray.y += dir.end.y * 0.1;
		pixel_image(&game->img_w, game->pos.ray.x, game->pos.ray.y, 0xFF0000);
		if (game->pos.ray.y >= HEIGHT || game->pos.ray.x >= WIDTH
			|| game->pos.ray.x <= 0 || game->pos.ray.y <= 0)
			break ;
	}
}

void	loop_ray(t_vec dir, t_game *game)
{
	double	limit;
	bool	complete;

	limit = game->pos.angle;
	complete = false;
	pixel_image(&game->img_w, dir.start.x, dir.start.y, 0xFFFFFF);
	dir.end.x = cos(game->pos.angle);
	dir.end.y = sin(game->pos.angle);
	ray(game, dir);
	while (game->pos.angle > (limit - degrees(30)))
	{
		while (complete == false)
		{
			game->pos.angle += degrees(0.1); // Menos de un grado
			dir.end.x = cos(game->pos.angle);
			dir.end.y = sin(game->pos.angle);
			ray(game, dir);
			if (game->pos.angle > (limit + degrees(30)))
			{
				complete = true;
				game->pos.angle = limit;
			}
		}
		game->pos.angle -= degrees(0.1);
		dir.end.x = cos(game->pos.angle);
		dir.end.y = sin(game->pos.angle);
		ray(game, dir);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0);
	game->pos.angle = limit;
}

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	// if (parse_game(&game, argc, argv) == 1)
	// 	return (1);
	game.pos.angle = degrees(270);
	game.pos.dir.start.x = 350;
	game.pos.dir.start.y = 300;
	game.keys.s = 0;
	game.keys.a = 0;
	init_window(&game);
	loop_ray(game.pos.dir, &game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game); // Save key pressed
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game); // Save key release
	mlx_loop_hook(game.mlx, ft_events, &game);
	mlx_loop(game.mlx);
	// free_end(&game); // TODO: free all allocated memory
}
