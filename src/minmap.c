/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:37:18 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/20 23:19:53 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minmap(t_minmap *map)
{
	map->color_floor = 0xFFFF00;
	map->color_player = 0x00FF00;
	map->color_wall = 0x0000FF;
	map->color_floor = 0x000000;
	map->edge_x = 20; // La margen será de dos cuadritos
	map->edge_y = 20;
	map->scale = 10; // 10x10 sera el tamaño de una unidad del mapa
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
	// mlx_put_image_to_window(game->mlx, game->win, game->img.ptr, 0, 0);
}

void	mini_map(t_game *game)
{
	init_minmap(&game->mp);
	render_minmap(game);
}
