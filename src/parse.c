/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 17:37:34 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/22 16:34:32 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	push_lst(t_list **head, t_list **tail, char **line, ssize_t len)
{
	t_list	*new_node;

	if (*line[0] == '\n')
		return (ft_freestr(line), 0);
	new_node = ft_lstnew(*line);
	if (new_node == NULL)
		return (perror_malloc(), 1);
	if (*head == NULL)
		*head = new_node;
	else
		(*tail)->next = new_node;
	*tail = new_node;
	return (0);
	(void)len;
}

ssize_t	read_file(int fd, t_list **head, char *filename)
{
	t_list	*tail;
	char	*line;
	ssize_t	bytes_read;
	ssize_t	lines;

	*head = NULL;
	tail = NULL;
	line = NULL;
	lines = 0;
	while (1)
	{
		bytes_read = get_next_line(fd, &line);
		if (bytes_read == -1)
			return (perror_gnl(filename),
				ft_freestr(&line), ft_lstclear(head, free), -1);
		if (bytes_read == 0)
			break ;
		if (push_lst(head, &tail, &line, bytes_read) == 1)
			return (ft_freestr(&line), ft_lstclear(head, free), -1);
		lines++;
	}
	return (lines);
}

int	parse_game(t_game *game, int argc, char **argv)
{
	size_t	len;
	int		fd;
	t_list	*file_lines;
	ssize_t	lines_count;

	if (argc != 2)
		return (perror_args());
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(&argv[1][len - 4], ".cub", 4) != 0)
		return (perror_filename());
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror_open(argv[1]));
	lines_count = read_file(fd, &file_lines, argv[1]);
	close(fd);
	if (lines_count == -1)
		return (ft_lstclear(&file_lines, free), 1);
	for (t_list *tmp = file_lines; tmp != NULL; tmp = tmp->next)
		printf("%s", (char *)tmp->content);
	ft_lstclear(&file_lines, free);
	return (0);
	(void)game;
}
