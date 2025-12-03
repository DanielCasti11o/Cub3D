/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacastil <dacastil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 16:50:08 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/03 17:06:08 by dacastil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall(t_game *game, double x, double y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (1);
	if (game->map.grid[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	move_vector_view(int type, t_game *game)
{
	t_vec2f	mv;
	double	speed;
	double	margin;

	speed = 0.04;
	if (type == FRONT)
	{
		mv.x = cosf(game->player.angle) * speed;
		mv.y = sinf(game->player.angle) * speed;
	}
	else
	{
		mv.x = -cosf(game->player.angle) * speed;
		mv.y = -sinf(game->player.angle) * speed;
	}
	margin = 0.2;
	if (mv.x < 0)
		margin = -margin;
	if (!is_wall(game, game->player.pos.x + mv.x + margin, game->player.pos.y))
		game->player.pos.x += mv.x;
	margin = MARGIN;
	if (mv.y < 0)
		margin = -margin;
	if (!is_wall(game, game->player.pos.x, game->player.pos.y + mv.y + margin))
		game->player.pos.y += mv.y;
}

void	lateral_transition(int type, t_game *game)
{
	t_vec2f	mv;
	double	speed;
	double	angle;
	double	margin;

	speed = 0.03;
	if (type == RIGHT)
		angle = game->player.angle + (PI / 2);
	else
		angle = game->player.angle - (PI / 2);
	mv.x = cosf(angle) * speed;
	mv.y = sinf(angle) * speed;
	margin = 0.2;
	if (mv.x < 0)
		margin = -margin;
	if (!is_wall(game, game->player.pos.x + mv.x + margin, game->player.pos.y))
		game->player.pos.x += mv.x;
	margin = MARGIN;
	if (mv.y < 0)
		margin = -margin;
	if (!is_wall(game, game->player.pos.x, game->player.pos.y + mv.y + margin))
		game->player.pos.y += mv.y;
}
