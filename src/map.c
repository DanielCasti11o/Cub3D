/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:45:49 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/31 22:34:17 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_map_char(char c)
{
	return (c == ' ' || c == '0' || c == '1' || is_player_char(c));
}

static int	is_void_like(char c)
{
	return (c == ' ' || c == '\0' || c == '\n');
}

static int	save_mapline(t_game *game, t_parse *parse, const char *line, size_t i)
{
	ssize_t	len;
	size_t	col;

	game->parse.map.grid[i] = malloc(sizeof(char) * (game->parse.map.width + 1));
	if (game->parse.map.grid[i] == NULL)
		return (perror_malloc());
	game->parse.map.grid[i][game->parse.map.width] = '\0';
	len = parse->first_v_char;
	while (line[len] != '\0' && line[len] != '\n' && len < parse->last_v_char)
	{
		if (!is_map_char(line[len]))
			return (perror_unexpectedchar(line[len]), ft_freestr(&game->parse.map.grid[i]), 1);
		col = len - parse->first_v_char;
		if (is_player_char(line[len]))
		{
			if (game->parse.map.player_start_x != -1
				&& game->parse.map.player_start_y != -1)
				return (perror_multipleplayerstart(), ft_freestr(&game->parse.map.grid[i]), 1);
			game->parse.map.player_start_y = i;
			game->parse.map.player_start_x = col;
		}
		if (line[len] == '0' || is_player_char(line[len]))
		{
			if (i == 0 || is_void_like(game->parse.map.grid[i - 1][col])
				|| col == 0 || is_void_like(line[len - 1])
				|| col == game->parse.map.width - 1 || is_void_like(line[len + 1])
				|| i == game->parse.map.height - 1)
				return (perror_unclosedmap(), ft_freestr(&game->parse.map.grid[i]), 1);
		}
		if (line[len] == ' ')
		{
			if (i > 0 && (game->parse.map.grid[i - 1][col] == '0'
				|| is_player_char(game->parse.map.grid[i - 1][col])))
				return (perror_unclosedmap(), ft_freestr(&game->parse.map.grid[i]) ,1);
		}
		game->parse.map.grid[i][col] = line[len];
		len++;
	}
	while (len < parse->last_v_char)
	{
		col = len - parse->first_v_char;
		if (i > 0 && (game->parse.map.grid[i - 1][col] == '0'
			|| is_player_char(game->parse.map.grid[i - 1][col])))
			return (perror_unclosedmap(), ft_freestr(&game->parse.map.grid[i]), 1);
		game->parse.map.grid[i][col] = ' ';
		len++;
	}
	return (0);
}

int	parse_map(t_game *game, t_parse *parse)
{
	t_list	*tmp;
	size_t	i;

	if (parse->head_map == NULL)
		return (0);
	game->parse.map.width = parse->last_v_char - parse->first_v_char;
	game->parse.map.grid = malloc(sizeof(char *) * (game->parse.map.height + 1));
	game->parse.map.player_start_x = -1;
	game->parse.map.player_start_y = -1;
	if (game->parse.map.grid == NULL)
		return (perror_malloc());
	game->parse.map.grid[game->parse.map.height] = NULL;
	i = 0;
	while (i < game->parse.map.height)
	{
		if (save_mapline(game, parse, parse->head_map->content, i) == 1)
			return (ft_freestrarr(&game->parse.map.grid), 1);
		tmp = parse->head_map->next;
		ft_lstdelone(&parse->head_map, free);
		parse->head_map = tmp;
		i++;
	}
	if (game->parse.map.player_start_x == -1 || game->parse.map.player_start_y == -1)
		return (perror_noplayerstart(), ft_freestrarr(&game->parse.map.grid), 1);
	parse->seen |= E_MAP;
	return (0);
}
