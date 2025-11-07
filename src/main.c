/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/07 22:17:20 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray(t_game *game)
{
	game->pos.ray_x = game->pos.x;
	game->pos.ray_y = game->pos.y;
	while (1)
	{
		game->pos.ray_x += game->pos.to_x * 0.1;
		game->pos.ray_y += game->pos.to_y * 0.1;
		pixel_image(&game->img_w, game->pos.ray_x, game->pos.ray_y, 0xFF0000);
		if (game->pos.ray_y >= HEIGHT || game->pos.ray_x >= WIDTH
			|| game->pos.ray_x <= 0 || game->pos.ray_y <= 0)
			break ;
	}
}

void	loop_ray(t_game *game)
{
	double	limit;
	bool	complete;

	limit = game->vision.angle;
	complete = false;
	pixel_image(&game->img_w, game->pos.x, game->pos.y, 0xFFFFFF);
	game->pos.to_x = cos(game->vision.angle);
	game->pos.to_y = sin(game->vision.angle);
	ray(game);
	while (game->vision.angle > (limit - degrees(30)))
	{
		while (complete == false)
		{
			game->vision.angle += degrees(0.1); // Menos de un grado
			game->pos.to_x = cos(game->vision.angle);
			game->pos.to_y = sin(game->vision.angle);
			ray(game);
			if (game->vision.angle > (limit + degrees(30)))
			{
				complete = true;
				game->vision.angle =limit;
			}
		}
		game->vision.angle -= degrees(0.1);
		game->pos.to_x = cos(game->vision.angle);
		game->pos.to_y = sin(game->vision.angle);
		ray(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0);
	game->vision.angle = limit;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (parse_game(&game, argc, argv) == 1)
		return (1);
	game.vision.angle = degrees(270);
	game.pos.x = 350;
	game.pos.y = 300;
	game.keys.s = 0;
	game.keys.a = 0;
	init_window(&game);
	loop_ray(&game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game); // Save key pressed
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game); // Save key release
	mlx_loop_hook(game.mlx, ft_events, &game);
	mlx_loop(game.mlx);
	// free_end(&game); // TODO: free all allocated memory
}
