/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 17:27:26 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/10/30 22:00:26 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 700
# define HEIGHT 600

# include "structs.h"

# include "mlx.h"
# include "libft.h"

# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

int		perror_malloc(void);
int		perror_args(void);
int		perror_filename(void);
int		perror_open(char *filename);
int		perror_gnl(char *filename);

int		perror_unexpectedchar(char unexpected);
int		perror_alreadydefined(t_elemfile elem);
int		perror_overflow(void);
int		perror_missingelements(uint8_t seen);
int		perror_emptylineinmap(void);

t_color	color_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

int		parse_game(t_game *game, int argc, char **argv);

void	preinit_game(t_game *game);
void	init_window(t_game *game);
int		ft_events(t_game *game);
void	loop_ray(t_game *game);
int		ft_key_press(int keycode, t_game *game);
int		ft_key_release(int keycode, t_game *game);
void	loop_ray(t_game *game);

#endif
