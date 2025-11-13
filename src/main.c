/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/13 21:22:10 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	(void)argc;
	(void)argv;
	if (parse_game(&game, argc, argv) == 1)
		return (1);
	printf("startx = %f starty= %f", game.player.pos.x, game.player.pos.y);
	game.keys.s = 0;
	game.keys.a = 0;
	game.player.fov_tan = tan(degrees(ANGLE_FOV / 2));
	init_window(&game);
	raycasting(&game);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game); // Save key pressed
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game); // Save key release
	mlx_loop_hook(game.mlx, ft_events, &game);
	mlx_loop(game.mlx);
	free_end(&game); // TODO: free all allocated memory
}
