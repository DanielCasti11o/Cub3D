/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:43:02 by migugar2          #+#    #+#             */
/*   Updated: 2025/10/31 22:26:18 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h> // bool
# include <stdint.h> // int, uint types
# include <stddef.h> // size_t
# include "libft.h" // t_list

// This structure draws everything in an invisible buffer
//  that stores all the information about everything that will later
// be drawn on the screen, thus avoiding flickering.

// < This concept is called "Double Buffering." >
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_pos
{
	float	x;
	float	y;
	float	to_x;
	float	to_y;
	float	ray_x;
	float	ray_y;
	bool	is_inside; // algorithm bsp rectangle adaptation
	int		value; // key in map
}	t_pos;

typedef struct s_textures
{
	void	*wall;
	void	*flood;
	void	*door;
	void	*flash; // Is opcional.
	void	*sphere; // Ray tracing
	void	*mini_map;
}	t_texture;

typedef struct s_vision
{
	long	triangle; // triangle of vision in the map
	bool	sphere_inside; // bsp triangule vision
	float	angle;
}	t_vision;

typedef struct s_keys
{
	int	a;
	int	w;
	int	s;
	int	d;
	int	right;
	int	left;
	int	up;
	int	down;
}	t_keys;

typedef struct s_color
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a; // alpha channel, probably not used
}	t_color;

typedef enum e_elemfile
{
	E_NO = 1 << 0,
	E_SO = 1 << 1,
	E_WE = 1 << 2,
	E_EA = 1 << 3,
	E_F = 1 << 4,
	E_C = 1 << 5,
	E_MAP = 1 << 6,
	E_EMPTY = 1 << 7,
	E_INVALID = 1 << 8
}	t_elemfile;

typedef enum e_stateparse
{
	SP_HEADER,
	SP_MAP,
	SP_DONE
}	t_stateparse;

// This is only an initial simple example
typedef struct s_map
{
	size_t	width;
	size_t	height;
	char	**grid;
	int		player_start_x; // x & y can be 2d vector
	int		player_start_y;
}	t_map;

typedef struct s_parse
{
	t_list			*head_map;
	t_list			*tail_map;
	uint8_t			seen;
	t_stateparse	state;
	ssize_t			first_v_char;
	ssize_t			last_v_char;
}	t_parse;

typedef struct s_infile
{
	t_map	map;
	t_color	f;
	t_color	c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_infile;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	t_pos		pos;
	t_vision	vision;
	t_texture	textures;
	t_keys		keys;
	t_infile	parse;
	t_img		img_w;
}	t_game;

#endif
