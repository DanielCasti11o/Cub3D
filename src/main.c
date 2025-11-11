/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/11 20:00:31 by daniel-cast      ###   ########.fr       */
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
	// game.pos.angle = degrees(270);
	printf("startx = %f starty= %f", game.pos.dir.start.x, game.pos.dir.start.y);
	game.keys.s = 0;
	game.keys.a = 0;
	init_window(&game);
	for(int i = 0; game.pos.map.grid[i]; i++)
		printf("%s\n", game.pos.map.grid[i]);
	raycasting(&game, game.pos.dir);
	mlx_hook(game.win, 2, 1L << 0, ft_key_press, &game); // Save key pressed
	mlx_hook(game.win, 3, 1L << 1, ft_key_release, &game); // Save key release
	mlx_loop_hook(game.mlx, ft_events, &game);
	mlx_loop(game.mlx);
	// free_end(&game); // TODO: free all allocated memory
}
