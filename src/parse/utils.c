/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 20:35:50 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/06 21:14:24 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	t_color	out;

	out.r = r;
	out.g = g;
	out.b = b;
	out.a = a;
	return (out);
}

void	preinit_parse(t_game *game, t_parse *parse)
{
	game->pos.map.height = 0;
	parse->first_v_char = -1;
	parse->last_v_char = 0;
	parse->head_map = NULL;
	parse->tail_map = NULL;
	parse->state = SP_HEADER;
	game->infile.c = color_rgba(0, 0, 0, 0);
	game->infile.f = color_rgba(0, 0, 0, 0);
	game->infile.no = NULL;
	game->infile.so = NULL;
	game->infile.we = NULL;
	game->infile.ea = NULL;
}

int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || is_player_char(c));
}

int	is_void_char(char c)
{
	return (c == ' ' || c == '\0' || c == '\n');
}

/*
uint32_t	pack_color(int endian, t_color color)
{
	uint32_t	packed;

	if (endian == 0)
		packed = (((uint32_t)color.a << 24)
				| (color.r << 16) | (color.g << 8) | color.b);
	else
		packed = ((color.a) | (color.r << 8) | (color.g << 16)
				| ((uint32_t)color.b << 24));
	return (packed);
}

t_color	unpack_color(int endian, uint32_t packed)
{
	t_color	color;

	if (endian == 0)
	{
		color.a = (packed >> 24) & 0xFF;
		color.r = (packed >> 16) & 0xFF;
		color.g = (packed >> 8) & 0xFF;
		color.b = packed & 0xFF;
	}
	else
	{
		color.a = packed & 0xFF;
		color.r = (packed >> 8) & 0xFF;
		color.g = (packed >> 16) & 0xFF;
		color.b = (packed >> 24) & 0xFF;
	}
	return (color);
}
*/
