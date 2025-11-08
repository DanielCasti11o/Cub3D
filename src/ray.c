/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel-castillo <daniel-castillo@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 18:31:06 by daniel-cast       #+#    #+#             */
/*   Updated: 2025/11/08 20:53:00 by daniel-cast      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	algorithm_dda(t_game *game, t_vec dir)
{
	int		mapx; // celda donde esta posicionado realizamos aproximación.
	int		mapy; // celda donde esta posicionado
	int		stepx; // Dirección -1 siendo izquierda y +1 derecha.
	int		stepy;
	double	deltaX;
	double	deltaY;
	float	side_distx; // Recta de la distancia IMPORTANTE el concepto = RECTA.
	float	side_disty;


	// Aqui aproximamos el flotante a la unidad como tal para indicar la posición de la celda completa.
	mapx = (int)dir.start.x;
	mapy = (int)dir.start.y;

	// deltas de {x, y}, Distancia para cruzar desde la posición dentro de la unidad en la que estoy hasta el fin de la unidad.
	deltaX = 1.0 / fabs(dir.end.x);
	deltaY = 1.0 / fabs(dir.end.y);
	if (dir.end.x < 0) // EJE X = left
	{
		stepx = -1;
		side_distx = (dir.start.x - mapx) * deltaX; // Aqui estamos restando (la unidad completa) con (la posicion del jugador) y eso
		// multiplicandolo con (la linea del rayo desde el jugador hasta el borde de la unidad) para hallar (la distancia en linea recta de lo que debe recorrer).
	}
	else // right
	{
		stepx = 1;
		side_distx = (mapx + 1.0 - dir.start.x) * deltaX; // + 1.0 porque a la unidad que va a avanzar es el inicio de la siguiente unidad ej: 0.5 derecha es 1
		// en la anterior no ponemos nada porque a la izquierda de 0.5 es el mismo 0
	}
	if (dir.end.y < 0) // EJE Y = left
	{
		stepy = -1;
		side_disty = (dir.start.y - mapy) * deltaY;
	}
	else // right
	{
		stepy = 1;
		side_distx = (mapy + 1.0 - dir.start.y) * deltaY; // + 1.0 porque en el eje {Y} abajo suma más.
	}

	// Check HIT  pendiente...
}

void	ray(t_game *game, t_vec dir)
{
	game->pos.ray.x = dir.start.x;
	game->pos.ray.y = dir.start.y;
	while (1)
	{
		game->pos.ray.x += dir.end.x * 0.1;
		game->pos.ray.y += dir.end.y * 0.1;
		pixel_image(&game->img_w, game->pos.ray.x, game->pos.ray.y, 0xFF0000);
		if (game->pos.ray.y >= HEIGHT || game->pos.ray.x >= WIDTH
			|| game->pos.ray.x <= 0 || game->pos.ray.y <= 0)
			break ;
	}
}

void	loop_ray(t_vec dir, t_game *game)
{
	double	limit;
	bool	complete;

	limit = game->pos.angle;
	complete = false;
	pixel_image(&game->img_w, dir.start.x, dir.start.y, 0xFFFFFF);
	dir.end.x = cos(game->pos.angle);
	dir.end.y = sin(game->pos.angle);
	ray(game, dir);
	algorithm_dda(game, dir);
	// while (game->pos.angle > (limit - degrees(30)))
	// {
	// 	while (complete == false)
	// 	{
	// 		game->pos.angle += degrees(0.1); // Menos de un grado
	// 		dir.end.x = cos(game->pos.angle);
	// 		dir.end.y = sin(game->pos.angle);
	// 		ray(game, dir);
	// 		if (game->pos.angle > (limit + degrees(30)))
	// 		{
	// 			complete = true;
	// 			game->pos.angle = limit;
	// 		}
	// 	}
	// 	game->pos.angle -= degrees(0.1);
	// 	dir.end.x = cos(game->pos.angle);
	// 	dir.end.y = sin(game->pos.angle);
	// 	ray(game, dir);
	// }
	mlx_put_image_to_window(game->mlx, game->win, game->img_w.img, 0, 0);
	game->pos.angle = limit;
}
