/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:19:45 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/12/02 19:47:32 by daniel-cast      ###   ########.fr       */
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
	mlx_mouse_hide(game->mlx, game->win);
	mouse = init_mouse();
	if (mouse.enabled == 0)
		return (0);
	delta.x = x - mouse.center_x;
	delta.y = y - mouse.center_y;
	if (delta.x != 0)
	{
		if (delta.x < 0)
			game->player.angle -= degrees(0.3);
		else
			game->player.angle += degrees(0.3);
		if (delta.y < 0)
			game->player.pitch += 3;
		else
			game->player.pitch -= 3;
		mlx_mouse_move(game->mlx, game->win,
			mouse.center_x, mouse.center_y);
	}
	return (0);
}
