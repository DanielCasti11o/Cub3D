/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:25:05 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/20 23:17:20 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	if (parse_game(&game, argc, argv) == 1)
		return (1);
	printf("startx = %f starty= %f\n", game.player.pos.x, game.player.pos.y);
	if (init_game(&game) == 1)
		return (free_end(&game), 1);
	raycasting(&game);
	mini_map(&game);
	mlx_loop(game.mlx);
	free_end(&game);
	return (0);
}
