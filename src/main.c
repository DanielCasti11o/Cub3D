/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/21 16:59:39 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray(t_game *game)
{
	game->pos.ray_x += game->pos.to_x * 0.1;
	game->pos.ray_y += game->pos.to_y * 0.1;
	printf("%f %f \n", game->pos.ray_y, game->pos.ray_x);
}

void	loop_ray(t_game *game)
{
	game->pos.x = 350;
	game->pos.y = 300;
	game->pos.ray_x = game->pos.x;
	game->pos.ray_y = game->pos.y;
	game->vision.angle = 1.5708;
	mlx_pixel_put(game->mlx, game->win, game->pos.x, game->pos.y, 0xFFFFFF);
	game->pos.to_x = cos(game->vision.angle);
	game->pos.to_y = sin(game->vision.angle);
	while (1)
	{
		ray(game);
		printf("o\n");
		mlx_pixel_put(game->mlx, game->win, game->pos.ray_x, game->pos.ray_y, 0xFF0000);
		if (game->pos.ray_y >= HEIGHT || game->pos.ray_x >= WIDTH
			|| game->pos.ray_x <= 0 || game->pos.ray_y <= 0)
			break ;
	}
	printf("sale\n");
}

// void	print_ray(int x, int y, float angle, t_game *game)
// {
// 	game->pos.to_x = (x * cos(angle)) - (y * sin(angle));
// 	game->pos.to_y = (x * sin(angle)) + (y * cos(angle));
// }


int	main()
{
	t_game	game;

	init_window(&game);
	loop_ray(&game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game); // Save key pressed
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game); // Save key release
	mlx_loop(game.mlx);
	mlx_loop_hook(game.mlx, ft_events, &game);
}
