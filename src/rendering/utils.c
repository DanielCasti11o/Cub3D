/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:01:16 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/02 17:32:58 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(t_game *game, t_dda *dda)
{
	if (dda->map.x < 0 || dda->map.x >= (int)game->map.width
		|| dda->map.y < 0 || dda->map.y >= (int)game->map.height)
		return (1);
	if (game->map.grid[dda->map.y][dda->map.x] == '1')
		return (1);
	return (0);
}

double	apply_fisheye_correction(t_game *game, t_dda *dda, double dist)
{
	double	proj_cos;

	proj_cos = game->player.dir.x * dda->rdir.x
		+ game->player.dir.y * dda->rdir.y;
	if (proj_cos != 0)
		dist /= proj_cos;
	if (dist < 0.0001)
		dist = 0.0001;
	return (dist);
}

int	is_door_tile(char c)
{
	return (c == 'H' || c == 'V');
}

void	draw_door(t_game *game, int x, int y, int type)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->mp.scale)
	{
		j = 0;
		while (j < game->mp.scale)
		{
			if (type == 'V')
			{
				if (j >= ((game->mp.scale / 2) - 2) && j <= (game->mp.scale / 2) + 2)
					pixel_image(&game->img, x + j, y + i, 0x00A52A2A);
				else
					pixel_image(&game->img, x + j, y + i, game->mp.color_floor);
			}
			if (type == 'H')
			{
				if (i >= ((game->mp.scale / 2) - 2) && i <= (game->mp.scale / 2) + 2)
					pixel_image(&game->img, x + j, y + i, 0x00A52A2A);
				else
					pixel_image(&game->img, x + j, y + i, game->mp.color_floor);
			}
			j++;
		}
		i++;
	}
}
