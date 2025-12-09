/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:06:32 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/08 00:43:30 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_textpath(t_game *game, t_elemfile elem, char *l, size_t strt)
{
	size_t	len;
	char	*path;

	strt = 0;
	while (ft_isspace(l[strt]))
		strt++;
	len = 0;
	while (l[strt + len] != '\0' && l[strt + len] != '\n')
		len++;
	while (len > 0 && ft_isspace(l[strt + len - 1]))
		len--;
	if (len == 0)
		return (perror_emptyarg(elem));
	path = ft_substr(l, strt, len);
	if (path == NULL)
		return (perror_malloc());
	if (elem == E_NO)
		return (game->infile.no = path, 0);
	else if (elem == E_SO)
		return (game->infile.so = path, 0);
	else if (elem == E_WE)
		return (game->infile.we = path, 0);
	else if (elem == E_EA)
		return (game->infile.ea = path, 0);
	return (game->infile.door = path, 0);
}

static int	parse_color_component(char **str, uint8_t *component)
{
	int	value;

	while (ft_isspace(**str))
		(*str)++;
	if (**str == '+')
		(*str)++;
	if (!ft_isdigit(**str))
		return (perror_unexpectedchar(**str), 1);
	value = 0;
	while (ft_isdigit(**str))
	{
		value = value * 10 + (**str - '0');
		if (value > 255)
			return (perror_overflow(), 1);
		(*str)++;
	}
	*component = (uint8_t)value;
	while (ft_isspace(**str))
		(*str)++;
	return (0);
}

static int	parse_color(t_game *game, t_elemfile type, char *line)
{
	t_color	*color;

	if (type == E_F)
		color = &game->infile.f;
	else
		color = &game->infile.c;
	if (parse_color_component(&line, &color->r) == 1)
		return (1);
	if (*line != ',')
		return (perror_unexpectedchar(*line), 1);
	line++;
	if (parse_color_component(&line, &color->g) == 1)
		return (1);
	if (*line != ',')
		return (perror_unexpectedchar(*line), 1);
	line++;
	if (parse_color_component(&line, &color->b) == 1)
		return (1);
	if (*line != '\n' && *line != '\0')
		return (perror_unexpectedchar(*line), 1);
	color->a = 255;
	return (0);
}

static t_elemfile	identify_header(char **line)
{
	while (ft_isspace(**line))
		(*line)++;
	if ((*line)[0] == 'N' && (*line)[1] == 'O')
		return (*line += 2, E_NO);
	else if ((*line)[0] == 'S' && (*line)[1] == 'O')
		return (*line += 2, E_SO);
	else if ((*line)[0] == 'W' && (*line)[1] == 'E')
		return (*line += 2, E_WE);
	else if ((*line)[0] == 'E' && (*line)[1] == 'A')
		return (*line += 2, E_EA);
	else if (BONUS && (*line)[0] == 'D' && (*line)[1] == 'O')
		return (*line += 2, E_DO);
	else if ((*line)[0] == 'F')
		return (*line += 1, E_F);
	else if ((*line)[0] == 'C')
		return (*line += 1, E_C);
	if ((*line)[0] == '1' || (*line)[0] == '0' || (*line)[0] == 'N'
		|| (*line)[0] == 'S' || (*line)[0] == 'E' || (*line)[0] == 'W')
		return (E_MAP);
	else if (**line == '\0' || **line == '\n')
		return (E_EMPTY);
	return (E_INVALID);
}

int	parse_header(t_game *game, char	*line, t_parse	*parse)
{
	t_elemfile	type;

	type = identify_header(&line);
	if (type == E_INVALID)
		return (perror_unexpectedchar(*line));
	else if (type == E_EMPTY)
		return (0);
	else if (type == E_MAP)
	{
		if ((parse->seen & parse->mandatory) != parse->mandatory)
			return (parse->seen |= E_MAP, perror_missingelements(parse->seen));
		parse->state = SP_MAP;
		return (0);
	}
	if (parse->seen & type)
		return (perror_alreadydefined(type));
	parse->seen |= type;
	if (!ft_isspace(*line))
		return (perror_unexpectedchar(*line));
	if (type == E_C || type == E_F)
		return (parse_color(game, type, line));
	return (parse_textpath(game, type, line, 0));
}
