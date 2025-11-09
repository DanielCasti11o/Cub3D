/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:31:06 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/09 11:28:15 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_hit(t_game *game, t_vec dir, t_dda dda)
{
	double	wall_dist;

	if (game->pos.map.grid[dda.map.y][dda.map.y] == 1) // Sí en la celda que estoy es 1 = pared choca.
	{
		dda.hit = 1;
	}
	if (dda.map.x < 0 || dda.map.x >= game->pos.map.width
		|| dda.map.y < 0 || dda.map.y >= game->pos.map.height)
		return (1); // con esto si el rayo se sale del mapa, se detiene.
	return (0);
}

void	steps(t_dda dda, t_game *game, t_vec dir)
{
	if (dir.end.x < 0) // EJE X = left
	{
		dda.step.x = -1;
		dda.side_dist.x = (dir.start.x - dda.map.x) * dda.deltax; // Aqui estamos restando (la unidad completa) con (la posicion del jugador) y eso
		// multiplicandolo con (la linea del rayo desde el jugador hasta el borde de la unidad) para hallar (la distancia en linea recta de lo que debe recorrer).
	}
	else // right
	{
		dda.step.x = 1;
		dda.side_dist.x = (map.x + 1.0 - dir.start.x) * dda.deltax; // + 1.0 porque a la unidad que va a avanzar es el inicio de la siguiente unidad ej: 0.5 derecha es 1
		// en la anterior no ponemos nada porque a la izquierda de 0.5 es el mismo 0
	}
	if (dir.end.y < 0) // EJE Y = Up
	{
		dda.step.y = -1;
		dda.side_dist.y = (dir.start.y - dda.map.y) * dda.deltay;
	}
	else // Down
	{
		dda.step.y = 1;
		dda.side_dist.x = (dda.map.y + 1.0 - dir.start.y) * dda.deltay; // + 1.0 porque en el eje {Y} abajo suma más.
	}
}

void	fpredrawing(t_game *game, t_vec dir, t_dda dda)
{
	// Si side es 0, el rayo golpeó en el eje x
	if (dda.side == 0)
	{
		// Fórmula: Distancia recorrida en X perpendicular
		dda.ppdist_wall = (dda.map.x - dir.start.x + (1 - dda.step.x) / 2.0)
			/ dir.end.x;
	}
	// Si side es 1, el rayo golpeó en el eje y.
	else
	{
		// Fórmula: Distancia recorrida en Y perpendicular
		dda.ppdist_wall = (dda.map.y - dir.start.y + (1 - dda.step.y) / 2.0)
			/ dir.end.y;
	}
	if (dda.ppdist_wall < 0.0001) // Evitamos division por cero
		dda.ppdist_wall = 0.0001;
	dda.line_height = (int)(HEIGHT / dda.ppdist_wall);
}

void	limdrawing(t_game *game, t_vec dir, t_dda dda)
{
	int	draw_start;
	int	draw_end;

	draw_start = HEIGHT / 2 - dda.line_height / 2; // Inicia en = (mitad de la altura de pantalla) - (mitad de la altura de la pared)

	if (draw_start < 0) // Guardarrail
		draw_start = 0;
	draw_end = HEIGHT / 2 + dda.line_height / 2; // Termina en = (mitad de la altura de pantalla) + (mitad de la altura de la pared)
	if (draw_end >= HEIGHT) // Guardarraíl
		draw_end = HEIGHT - 1;
}

void	raycasting(t_game *game, t_vec dir)
{
	t_dda	dda;

	dda.hit	= 0;
	dda.map.x = (int)dir.start.x; // Aqui aproximamos el flotante a la unidad como tal para indicar la posición de la celda completa.
	dda.map.y = (int)dir.start.y;
	dda.deltax = 1.0 / fabs(dir.end.x);
	dda.deltay = 1.0 / fabs(dir.end.y);
	dir.end.x = cos(game->pos.angle);
	dir.end.y = sin(game->pos.angle);
	steps(dda, game, dir);
	// Proyección 3D
	// Conversión de la distancia en linea recta del recorrido del rayo en la altura de la pared cuando choca.
	dda_loop(game, dir, dda);
	fpredrawing(game, dir, dda); // Aquí hacemos las ecuaciones que apunte
	lim_drawing(game, dir, dda); // Definimos limites de dibujado
	// pendiente loop de dibujado...
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0); // poner la imagen ya dibujada en el buffering.
}

void	dda_loop(t_game *game, t_vec dir, t_dda dda)
{
	while (!dda.hit)
	{
		if (dda.side_dist.x < dda.side_dist.y)
		{
			dda.side_dist.x += dda.deltax; // Suma el 'precio' para ir al siguiente X
			dda.map.x += dda.step.x; // Mueve incrementando la posición de la celda X
			dda.side = 0; // Golpeó una pared eje x
		}
		else
		{
			dda.side_dist.y += dda.deltay; // Suma el 'precio' para ir al siguiente Y
			dda.map.y += dda.step.y; // Mueve incrementando la posición de la celda Y
			dda.side = 1; // Golpeó una pared eje y
		}
		check_hit(game, dir, dda);
	}
}
