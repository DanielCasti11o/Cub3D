/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:19:45 by dacastil          #+#    #+#             */
/*   Updated: 2025/12/03 18:18:22 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_mouse	init_mouse(void)
{
	t_mouse	mouse;

	mouse.center_x = WIDTH / 2;
	mouse.center_y = HEIGHT / 2;
	mouse.enabled = 1;
	return (mouse);
}

int	mouse_events(int x, int y, t_game *game)
{
	t_mouse		mouse;
	t_vec2i		delta;

	(void)y;
	mouse = init_mouse();
	if (mouse.enabled == 0)
		return (0);
	delta.x = x - mouse.center_x;
	delta.y = y - mouse.center_y;
	if (delta.x != 0)
		game->player.angle += degrees(delta.x * 0.05);
	if (delta.y != 0)
		game->player.pitch -= delta.y * 0.5;
	if (delta.y != 0 || delta.x != 0)
		mlx_mouse_move(game->mlx, game->win,
			mouse.center_x, mouse.center_y);
	return (0);
}
