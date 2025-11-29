/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:19:48 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/29 09:42:18 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_vector_view(int type, t_game *game)
{
	t_vec2f	new_pos;
	double	speed;

	speed = 0.03;
	if (type == FRONT)
	{
		new_pos.x = game->player.pos.x + cosf(game->player.angle) * speed;
		new_pos.y = game->player.pos.y + sinf(game->player.angle) * speed;
	}
	if (type == BACK)
	{
		new_pos.x = game->player.pos.x - cosf(game->player.angle) * speed;
		new_pos.y = game->player.pos.y - sinf(game->player.angle) * speed;
	}
	if (game->map.grid[(int)new_pos.y][(int)new_pos.x] != '1')
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
}

void	lateral_transition(int type, t_game *game)
{
	t_vec2f	new_pos;
	double	speed;

	speed = 0.03;
	if (type == RIGHT)
	{
		new_pos.x = game->player.pos.x
			+ cosf(game->player.angle + degrees(90)) * speed;
		new_pos.y = game->player.pos.y
			+ sinf(game->player.angle + degrees(90)) * speed;
	}
	if (type == LEFT)
	{
		new_pos.x = game->player.pos.x
			+ cosf(game->player.angle - degrees(90)) * speed;
		new_pos.y = game->player.pos.y
			+ sinf(game->player.angle - degrees(90)) * speed;
	}
	if (game->map.grid[(int)new_pos.y][(int)new_pos.x] != '1')
	{
		game->player.pos.x = new_pos.x;
		game->player.pos.y = new_pos.y;
	}
}

int	vertical_view(t_game *game, int type)
{
	int	new_pitch;

	new_pitch = game->player.pitch;
	if (type == UP)
	{
		if (game->player.pitch < (HEIGHT / 1.5))
			new_pitch = game->player.pitch + 5;
	}
	else if (type == DOWN)
	{
		if (game->player.pitch > -(HEIGHT / 1.5))
			new_pitch = game->player.pitch - 5;
	}
	return (new_pitch);
}
