/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: migugar2 <migugar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:43:02 by migugar2          #+#    #+#             */
/*   Updated: 2025/12/03 18:11:17 by migugar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>
# include <stdint.h>
# include <stddef.h>
# include "libft.h"

// * 2D vector with float precision
typedef struct s_vec2f
{
	float	x;
	float	y;
}	t_vec2f;

// * 2D vector with integer precision
typedef struct s_vec2i
{
	int	x;
	int	y;
}	t_vec2i;

// * 2D vector with double precision
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

/*
 * Double buffer image structure to avoid flickering
 * - ptr: mlx image pointer
 * - addr: pixel data address
 * - bpp: bits per pixel
 * - size_line: bytes per row
 */
typedef struct s_buf
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		width;
	int		height;
}	t_buf;

/*
 * Animation structure for sprite sequences
 * - frames: array of frame buffers
 * - frame_delay: delay between frames in game loops
 */
typedef struct s_anim
{
	t_buf	*frames;
	size_t	frame_count;
	size_t	current_frame;
	size_t	frame_delay;
	size_t	delay_counter;
}	t_anim;

/*
 * Game textures container
 * - c/f: ceiling and floor colors
 * - no/so/we/ea: cardinal wall textures
 * - door: door texture
 * - vm: view model animation
 */
typedef struct s_textures
{
	uint32_t	c;
	uint32_t	f;
	t_buf		no;
	t_buf		so;
	t_buf		we;
	t_buf		ea;
	t_buf		door;
	t_anim		vm;
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
 * - pos: world position
 * - angle: viewing angle in radians
 * - dir: normalized direction vector
 * - plane: camera plane for FOV
 * - pitch: vertical look offset
 */
typedef struct s_player
{
	t_vec2f	pos;
	float	angle;
	t_vec2f	dir;
	t_vec2f	plane;
	int		pitch;
}	t_player;

// * Mouse input state and configuration
typedef struct s_mouse
{
	int		enabled;
	double	sensitivity;
	int		center_x;
	int		center_y;
}	t_mouse;

// * Keyboard input state for movement and rotation
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
 * - E_DO: Optional door texture
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
	E_DO = 1 << 8,
	E_INVALID
}	t_elemfile;

/*
 * Minimap rendering configuration
 * - scale: tile size in pixels
 * - edge_x/edge_y: map boundary offsets
 * - wall/player: minimap textures
 */
typedef struct s_minmap
{
	int		scale;
	int		edge_x;
	int		edge_y;
	int		color_floor;
	int		color_wall;
	t_buf	wall;
	t_buf	player;
}	t_minmap;

// * Player position data for minimap rendering
typedef struct s_playermap
{
	t_vec2f	pos_float;
	t_vec2i	player_px;
	t_vec2i	center_px;
	int		scale_player;
	int		center;
}	t_playermap;

/*
 * Parsed input file data
 * - f/c: floor and ceiling colors
 * - no/so/we/ea: paths to cardinal textures
 * - door: path to door texture
 */
typedef struct s_infile
{
	t_color	f;
	t_color	c;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*door;
}	t_infile;

// * Movement direction for collision detection
typedef enum type_move
{
	FRONT,
	BACK,
	RIGHT,
	LEFT
}	t_type_move;

/*
 * Main game state container
 * - mlx/win: minilibx display pointers
 * - player: player state
 * - map: world map data
 * - keys: keyboard input state
 * - fov_tan: precomputed FOV tangent
 * - mp: minimap configuration
 */
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
	t_minmap	mp;
}	t_game;

// * Wall hit side for texture selection (NS or EW)
typedef enum e_side
{
	SIDE_VERTICAL,
	SIDE_HORIZONTAL
}	t_side;

/*
 * DDA raycasting algorithm state
 * - rdir: ray direction vector
 * - map: current grid cell position
 * - step: ray step direction (-1 or 1)
 * - delta: distance to cross one grid unit
 * - side_dist: distance to next grid line
 * - pdraw: pixel draw position
 * - hit: wall hit flag
 * - side: which wall side was hit (NS or EW)
 * - ppdist_wall: perpendicular wall distance (fisheye correction)
 * - line_height: wall stripe height in pixels
 * - draw_start/draw_end: vertical draw bounds
 * - camera_x: x-coordinate on camera plane [-1, 1]
 * - hit_door: door hit flag
 * - door_dist: perpendicular distance to door
 * - door_line_height: door stripe height in pixels
 * - door_draw_start/end: door vertical draw bounds
 * - door_map: grid position of the hit door
 * - door_type: door character type from map
 * - hit_door_side: side wall of door hit flag
 * - door_side_dist: distance to door side wall
 * - door_side_line_height: door side stripe height
 * - door_side_draw_start/end: door side vertical bounds
 */
typedef struct s_dda
{
	t_vec2f	rdir;
	t_vec2i	map;
	t_vec2i	step;
	t_vec2d	delta;
	t_vec2f	side_dist;
	t_vec2i	pdraw;
	int		hit;
	t_side	side;
	double	ppdist_wall;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	camera_x;
	int		hit_door;
	double	door_dist;
	int		door_line_height;
	int		door_draw_start;
	int		door_draw_end;
	t_vec2i	door_map;
	char	door_type;
	int		hit_door_side;
	double	door_side_dist;
	int		door_side_line_height;
	int		door_side_draw_start;
	int		door_side_draw_end;
}	t_dda;

/*
 * Column rendering data for texture mapping
 * - wall_x: exact hit position on wall [0.0, 1.0]
 * - tex_x: x-coordinate on texture
 * - step: texture y increment per screen pixel
 * - tex_pos: current texture y position (accumulator)
 * - y: current screen y-coordinate being drawn
 */
typedef struct s_column
{
	float	wall_x;
	int		tex_x;
	float	step;
	float	tex_pos;
	int		y;
}	t_column;

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
	t_list				*head_map;
	t_list				*tail_map;
	uint16_t			seen;
	uint16_t			mandatory;
	t_stateparse		state;
	ssize_t				first_v_char;
	ssize_t				last_v_char;
	ssize_t				player_start_x;
	ssize_t				player_start_y;
}	t_parse;

#endif
