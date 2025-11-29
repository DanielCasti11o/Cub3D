/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:37:18 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/29 17:11:28 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minmap(t_minmap *map)
{
	map->color_floor = 0xFFFF00;
	map->color_wall = 0x0000FF;
	map->color_floor = 0x000000;
	map->edge_x = 20;
	map->edge_y = 20;
	map->scale = 10;
}

void	draw_square(t_game *game, int x, int y, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->mp.scale)
	{
		j = 0;
		while (j < game->mp.scale)
		{
			pixel_image(&game->img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	render_minmap(t_game *game)
{
	t_vec2i	vec;
	t_vec2i	px;

	vec.y = 0;
	while (vec.y < (int)game->map.height)
	{
		vec.x = 0;
		while (vec.x < (int)game->map.width)
		{
			px.x = game->mp.edge_x + (vec.x * game->mp.scale);
			px.y = game->mp.edge_y + (vec.y * game->mp.scale);
			if (px.x < game->mp.edge_x + M_SIZE
				&& px.y < game->mp.edge_y + M_SIZE)
			{
				if (game->map.grid[vec.y][vec.x] == '1')
					draw_square(game, px.x, px.y, game->mp.color_wall);
				else if (game->map.grid[vec.y][vec.x] == '0'
					|| ft_strchr("NSEW", game->map.grid[vec.y][vec.x]))
					draw_square(game, px.x, px.y, game->mp.color_floor);
			}
			vec.x++;
		}
		vec.y++;
	}
}

void	render_player(t_game *game)
{
	t_vec2f	pos_float;
	t_vec2i	player_px;
	t_vec2i	count;
	int		scale_player;
	int		center;

	pos_float.x = game->player.pos.x;
	pos_float.y = game->player.pos.y;
	player_px.x = game->mp.edge_x + (int)(pos_float.x * game->mp.scale);
	player_px.y = game->mp.edge_y + (int)(pos_float.y * game->mp.scale);
	scale_player = M_PLAYER;
	center = scale_player / 2;
	count.y = 0;
	while (count.y < scale_player)
	{
		count.x = 0;
		while (count.x < scale_player)
		{
			pixel_image(&game->img, player_px.x + count.x - center,
				player_px.y + count.y - center, 0xff0000);
			count.x++;
		}
		count.y++;
	}
}

void	mini_map(t_game *game)
{
	init_minmap(&game->mp);
	render_minmap(game);
	render_player(game);
}
