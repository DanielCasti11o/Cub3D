/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/23 20:39:17 by daniel-cast      ###   ########.fr       */
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
	// printf("%f %f \n", game->pos.ray_y, game->pos.ray_x);
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
	while (game->vision.angle > (limit - 0.523599))
	{
		while (complete == false)
		{
			printf("aaa\n");
			game->vision.angle += 0.00174533; // Menos de un grado
			game->pos.to_x = cos(game->vision.angle);
			game->pos.to_y = sin(game->vision.angle);
			ray(game);
			if (game->vision.angle > (limit + 0.523599))
			{
				printf("bb\n");
				complete = true;
				game->vision.angle =limit;
			}
		}
		printf("ss\n");
		game->vision.angle -= 0.00174533;
		game->pos.to_x = cos(game->vision.angle);
		game->pos.to_y = sin(game->vision.angle);
		ray(game);
	}
	printf("sale");
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0);
	game->vision.angle = limit;
	// printf("sale\n");
}

// void	print_ray(int x, int y, float angle, t_game *game)
// {
// 	game->pos.to_x = (x * cos(angle)) - (y * sin(angle));
// 	game->pos.to_y = (x * sin(angle)) + (y * cos(angle));
// }


int	main()
{
	t_game	game;

	game.vision.angle = 4.71239;
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
}
