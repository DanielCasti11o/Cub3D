/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:43:02 by migugar2          #+#    #+#             */
/*   Updated: 2025/11/17 18:40:49 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h> // bool
# include <stdint.h> // int, uint types
# include <stddef.h> // size_t
# include "libft.h" // t_list

typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

typedef struct s_vec2d
{
	double	x;
	double	y;
}	t_vec2d;

// * 32-bit color in blue-green-red-alpha byte order (little-endian)
typedef struct s_color
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}	t_color;

// This structure draws everything in an invisible buffer
//  that stores all the information about everything that will later
// be drawn on the screen, thus avoiding flickering.

// < This concept is called "Double Buffering." >
typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		width;
	int		height;
}	t_buf;

typedef struct s_textures
{
	uint32_t	c;
	uint32_t	f;
	t_buf		no;
	t_buf		so;
	t_buf		we;
	t_buf		ea;
	/*
	void	*wall;
	void	*flood;
	void	*door;
	void	*flash; // Is opcional.
	void	*sphere; // Ray tracing
	void	*mini_map;
	*/
}	t_textures;

/*
 * Tile map stored as a grid of valid characters
 * - grid: array of characters, null-terminated array of null-terminated strings
 * - width: number of columns in the map
 * - height: number of rows in the map (excluding the null terminator)
 */
typedef struct s_map
{
	char		**grid;
	size_t		width;
	size_t		height;
	t_textures	tex;
}	t_map;

/*
 * Player position and direction in the game world
 * - map: the tile map
 *
 * // TODO
 */
typedef struct s_player
{
	t_vec2f	pos;
	float	angle;
	t_vec2f	dir;
	t_vec2f	plane;
	int		pitch;
	// t_vec2f	ray; // Point on the map where the ray is drawn
	// bool	is_inside; // algorithm bsp rectangle adaptation
	// int		value; // key in map
}	t_player;

typedef struct s_keys
{
	uint8_t	a;
	uint8_t	w;
	uint8_t	s;
	uint8_t	d;
	uint8_t	right;
	uint8_t	left;
	uint8_t	up;
	uint8_t	down;
}	t_keys;

/*
 * Bitmask enum to track which elements have been seen in the input file
 * - E_NO: North texture
 * - E_SO: South texture
 * - E_WE: West texture
 * - E_EA: East texture
 * - E_F: Floor color
 * - E_C: Ceiling color
 * - E_MAP: Map data
 * - E_EMPTY: Empty line (not marked in bitmask)
 * - E_INVALID: Invalid element (not marked in bitmask)
 */
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

/*
 * Input file data structure parsed
 * - f: floor color
 * - c: ceiling color
 * - no: path to north texture
 * - so: path to south texture
 * - we: path to west texture
 * - ea: path to east texture
 */
typedef struct s_infile
{
	t_color	f;
	t_color	c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_infile;

// TODO
typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
	t_keys		keys;
	t_infile	infile;
	t_buf		img;
	double		fov_tan;
	int			endian;
}	t_game;

typedef struct s_dda
{
	t_vec2f	rdir;
	t_vec2i	map; // punto dónde estamos parados sin float
	t_vec2i	step; // Dirección
	t_vec2d	delta; // deltas de x, y, Distancia para cruzar desde la posición dentro de la unidad en la que estoy hasta el fin de la unidad.
	t_vec2f	side_dist; // Recta de la distancia IMPORTANTE el concepto = RECTA.
	int		hit;
	int		side;	// Esto será una flag que lo que haga es indicar la linea de choque 0=Vertical Norte, Sur y 1=Horizontal {Este, Oeste}
	double	ppdist_wall; // Correción del ojo de pez (Distancia perpendicular)
	int		line_height;
	int		draw_start;
	int		draw_end;
	t_vec2i	pdraw;
	double	camera_x;
}	t_dda;

// * Parser state machine
typedef enum e_stateparse
{
	SP_HEADER,
	SP_MAP,
	SP_DONE
}	t_stateparse;

/*
 * Parser structure to hold parsing state and data
 * - head_map/tail_map: linked list of map lines, with O(1) append
 * - seen: bitmask of seen elements, using t_elemfile
 * - state: current state of the parser, using t_stateparse
 * - first_v_char: index of leftmost non-void column in the map
 * - last_v_char: index of rightmost non-void/exclusive column in the map
 * - player_start_(x/y): grid coordinates of the player spawn, -1 if not set
 */
typedef struct s_parse
{
	t_list			*head_map;
	t_list			*tail_map;
	uint8_t			seen;
	t_stateparse	state;
	ssize_t			first_v_char;
	ssize_t			last_v_char;
	ssize_t			player_start_x;
	ssize_t			player_start_y;
}	t_parse;

#endif
