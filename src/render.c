/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frukundo <frukundo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 03:32:27 by frukundo          #+#    #+#             */
/*   Updated: 2024/04/20 03:59:26 by frukundo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
	@desc:
	- updates the texture animations by moving to the next frame in the animation sequence.
	- For each texture direction (north, south, east, west):
	- Moves to the next frame (g->tex.n, g->tex.s, g->tex.e, g->tex.w).
	- If the end of the animation sequence is reached (g->tex.n is NULL),
		it resets to the beginning (g->tex.n_bak).
*/
void	update_anim(t_game *g)
{
	g->tex.n = g->tex.n->next;
	if (!g->tex.n)
		g->tex.n = g->tex.n_bak;
	g->tex.s = g->tex.s->next;
	if (!g->tex.s)
		g->tex.s = g->tex.s_bak;
	g->tex.e = g->tex.e->next;
	if (!g->tex.e)
		g->tex.e = g->tex.e_bak;
	g->tex.w = g->tex.w->next;
	if (!g->tex.w)
		g->tex.w = g->tex.w_bak;
}

/*
	@desc:
	- checks which movement keys are pressed and updates the player's position
		or rotation angle accordingly.
*/
void	check_move(t_game *g)
{
	if (g->pl.keys.left_pressed)
		g->ray.angle -= 3;
	if (g->pl.keys.right_pressed)
		g->ray.angle += 3;
	if (g->pl.keys.w_pressed)
		move_pl(KEY_W, g, 0, 0);
	if (g->pl.keys.a_pressed)
		move_pl(KEY_A, g, 0, 0);
	if (g->pl.keys.s_pressed)
		move_pl(KEY_S, g, 0, 0);
	if (g->pl.keys.d_pressed)
		move_pl(KEY_D, g, 0, 0);
}

/*
	@desc:
	- Checks if it's time to update based on the nframes and rate variables.
	- Updates animations every 2 frames.
	- Resets the player's door cooldown every 10 frames.
	- Calls check_move to update player movement.
	- Calls cub_raycast to perform raycasting and update the scene.
	- Inverts colors if g->neg is set.
	- Updates the game window with the new image.
*/
int	cub_update(void *param)
{
	t_game	*g;

	g = param;
	if (!(g->nframes % g->rate))
	{
		if (!(g->nframes % (2 * g->rate)))
			update_anim(g);
		if (!(g->nframes % (10 * g->rate)))
			g->pl.door_cooldown = 0;
		check_move(g);
		cub_raycast(g);
		if (g->neg == 1)
			cub_invert_color(g);
		mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->win_img.i, 0, 0);
	}
	g->nframes++;
	return (0);
}
