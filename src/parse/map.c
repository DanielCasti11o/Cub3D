/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:45:49 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/06 20:58:20 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	save_mapline(t_game *game, t_parse *parse, const char *line, size_t i)
{
	ssize_t	len;
	size_t	col;

	game->pos.map.grid[i] = malloc(sizeof(char) * (game->pos.map.width + 1));
	if (game->pos.map.grid[i] == NULL)
		return (perror_malloc());
	game->pos.map.grid[i][game->pos.map.width] = '\0';
	len = parse->first_v_char;
	while (line[len] != '\0' && line[len] != '\n' && len < parse->last_v_char)
	{
		if (!is_map_char(line[len]))
			return (perror_unexpectedchar(line[len]), ft_freestr(&game->pos.map.grid[i]), 1);
		col = len - parse->first_v_char;
		if (is_player_char(line[len]))
		{
			if (parse->player_start_x != -1
				&& parse->player_start_y != -1)
				return (perror_multipleplayerstart(), ft_freestr(&game->pos.map.grid[i]), 1);
			parse->player_start_y = i;
			parse->player_start_x = col;
		}
		if (line[len] == '0' || is_player_char(line[len]))
		{
			if (i == 0 || is_void_char(game->pos.map.grid[i - 1][col])
				|| col == 0 || is_void_char(line[len - 1])
				|| col == game->pos.map.width - 1 || is_void_char(line[len + 1])
				|| i == game->pos.map.height - 1)
				return (perror_unclosedmap(), ft_freestr(&game->pos.map.grid[i]), 1);
		}
		if (line[len] == ' ')
		{
			if (i > 0 && (game->pos.map.grid[i - 1][col] == '0'
				|| is_player_char(game->pos.map.grid[i - 1][col])))
				return (perror_unclosedmap(), ft_freestr(&game->pos.map.grid[i]) ,1);
		}
		game->pos.map.grid[i][col] = line[len];
		len++;
	}
	while (len < parse->last_v_char)
	{
		col = len - parse->first_v_char;
		if (i > 0 && (game->pos.map.grid[i - 1][col] == '0'
			|| is_player_char(game->pos.map.grid[i - 1][col])))
			return (perror_unclosedmap(), ft_freestr(&game->pos.map.grid[i]), 1);
		game->pos.map.grid[i][col] = ' ';
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
	game->pos.map.width = parse->last_v_char - parse->first_v_char;
	game->pos.map.grid = malloc(sizeof(char *) * (game->pos.map.height + 1));
	if (game->pos.map.grid == NULL)
		return (perror_malloc());
	parse->player_start_x = -1;
	parse->player_start_y = -1;
	game->pos.map.grid[game->pos.map.height] = NULL;
	i = 0;
	while (i < game->pos.map.height)
	{
		if (save_mapline(game, parse, parse->head_map->content, i) == 1)
			return (ft_freestrarr(&game->pos.map.grid), 1);
		tmp = parse->head_map->next;
		ft_lstdelone(&parse->head_map, free);
		parse->head_map = tmp;
		i++;
	}
	parse->tail_map = NULL;
	if (parse->player_start_x == -1 || parse->player_start_y == -1)
		return (perror_noplayerstart(), ft_freestrarr(&game->pos.map.grid), 1);
	parse->seen |= E_MAP;
	game->pos.dir.start.x = parse->player_start_x + 0.5f;
	game->pos.dir.start.y = parse->player_start_y + 0.5f;

	char	dir = game->pos.map.grid[parse->player_start_y][parse->player_start_x];
	if (dir == 'N')
	{
		game->pos.dir.end.x = 0.0f;
		game->pos.dir.end.y = -1.0f;
	}
	else if (dir == 'S')
	{
		game->pos.dir.end.x = 0.0f;
		game->pos.dir.end.y = 1.0f;
	}
	else if (dir == 'E')
	{
		game->pos.dir.end.x = 1.0f;
		game->pos.dir.end.y = 0.0f;
	}
	else if (dir == 'W')
	{
		game->pos.dir.end.x = -1.0f;
		game->pos.dir.end.y = 0.0f;
	}
	return (0);
}
