/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 21:07:59 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/02 16:28:29 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_player(t_game *game)
{
	if (game->keys.left == 1)
		game->player.angle -= degrees(0.5);
	if (game->keys.right == 1)
		game->player.angle += degrees(0.5);
	if (game->keys.d == 1)
		lateral_transition(RIGHT, game);
	if (game->keys.a == 1)
		lateral_transition(LEFT, game);
	if (game->keys.w == 1)
		move_vector_view(FRONT, game);
	if (game->keys.s == 1)
		move_vector_view(BACK, game);
	if (game->keys.up == 1)
		game->player.pitch += 5;
	if (game->keys.down == 1)
		game->player.pitch -= 5;
}

int	ft_game_loop(t_game *game)
{
	update_player(game);
	clear_image(&game->img);
	raycasting(game);
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
	return (0);
}
