/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:37:34 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/23 22:28:24 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	push_lst(t_list **head, t_list **tail, char **line)
{
	t_list	*new_node;

	if (*line[0] == '\n')
		return (ft_freestr(line), 0);
	new_node = ft_lstnew(*line);
	if (new_node == NULL)
		return (perror_malloc());
	if (*head == NULL)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
	return (0);
}

static t_list	*read_file(int fd, char *filename)
{
	t_list	*tail;
	char	*line;
	ssize_t	bytes_read;
	t_list	*head;

	head = NULL;
	tail = NULL;
	line = NULL;
	while (1)
	{
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			return (perror_gnl(filename),
				ft_freestr(&line), ft_lstclear(&head, free), NULL);
		if (bytes_read == 0)
			break ;
		if (push_lst(&head, &tail, &line) == 1)
			return (ft_freestr(&line), ft_lstclear(&head, free), NULL);
	}
	return (head);
}

static t_elemfile	identify_element(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (E_NO);
	else if (line[0] == 'S' && line[1] == 'O')
		return (E_SO);
	else if (line[0] == 'W' && line[1] == 'E')
		return (E_WE);
	else if (line[0] == 'E' && line[1] == 'A')
		return (E_EA);
	else if (line[0] == 'F')
		return (E_F);
	else if (line[0] == 'C')
		return (E_C);
	else
		return (E_MAP);
}

static int	parse_textpath(t_game *game, t_elemfile elem, char *line)
{
	size_t	len;
	char	*path;

	while (ft_isspace(*line))
		line++;
	len = 0;
	while (line[len] != '\0' && line[len] != '\n')
		len++;
	while (len > 0 && ft_isspace(line[len - 1]))
		len--;
	// TODO: must check if file is .xpm? Or let mlx handle it later?
	path = ft_substr(line, 0, len);
	if (path == NULL)
		return (perror_malloc());
	if (elem == E_NO)
		game->parse.no = path;
	else if (elem == E_SO)
		game->parse.so = path;
	else if (elem == E_WE)
		game->parse.we = path;
	else if (elem == E_EA)
		game->parse.ea = path;
	return (0);
}

static int	parse_map(t_game *game, t_list **file_lines, char *line)
{
	// TODO
	(void)game;
	(void)file_lines;
	(void)line;
	return (0);
}

static int	parse_line(t_game *game, t_list **file_lines, char *line)
{
	t_elemfile	elem;

	elem = identify_element(line);
	if (elem == E_MAP)
		return (parse_map(game, file_lines, line));
	// TODO: can be simplified with solved array int save_info
	if ((elem == E_C && game->parse.c.a != 0)
		|| (elem == E_F && game->parse.f.a != 0)
		|| (elem == E_NO && game->parse.no != NULL)
		|| (elem == E_SO && game->parse.so != NULL)
		|| (elem == E_WE && game->parse.we != NULL)
		|| (elem == E_EA && game->parse.ea != NULL))
		return (perror_alreadydefined(elem));
	if (elem == E_C || elem == E_F)
		line += 1;
	else
		line += 2;
	if (!ft_isspace(*line))
		return (perror_unexpectedchar(*line));
	if (elem == E_C)
		return (parse_color(line, &game->parse.c));
	else if (elem == E_F)
		return (parse_color(line, &game->parse.f));
	return (parse_textpath(game, elem, line));
}

static int	save_info(t_game *game, t_list **file_lines)
{
	char	solved[7];
	t_list	*tmp;

	while (*file_lines != NULL)
	{
		tmp = (*file_lines)->next;
		if (parse_line(game, file_lines, (*file_lines)->content) == 1)
			return (ft_lstclear(file_lines, free), 1);
		// TODO: can save here the value of t_elemfile, and delete parse_line function
		free((*file_lines)->content);
		free(*file_lines);
		*file_lines = tmp;
	}
	solved[E_NO] = (game->parse.no != NULL);
	solved[E_SO] = (game->parse.so != NULL);
	solved[E_WE] = (game->parse.we != NULL);
	solved[E_EA] = (game->parse.ea != NULL);
	solved[E_F] = (game->parse.f.a != 0);
	solved[E_C] = (game->parse.c.a != 0);
	solved[E_MAP] = 1; // (game->parse.map.grid != NULL);
	if (!solved[E_NO] || !solved[E_SO] || !solved[E_WE] || !solved[E_EA]
		|| !solved[E_F] || !solved[E_C] || !solved[E_MAP])
		return (perror_missingelements(solved), 1);
	return (0);
}

int	parse_game(t_game *game, int argc, char **argv)
{
	size_t	len;
	int		fd;
	t_list	*file_lines;

	if (argc != 2)
		return (perror_args());
	preinit_game(game);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		return (perror_filename());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror_open(argv[1]));
	file_lines = read_file(fd, argv[1]);
	close(fd);
	if (file_lines == NULL)
		return (1);
	if (save_info(game, &file_lines) == 1)
		return (1);
	return (0);
}
