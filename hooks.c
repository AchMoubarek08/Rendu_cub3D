/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:40:44 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/22 02:06:48 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	xclose(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

static int	key_pressed(int keycode, t_vars *vars)
{
	if (keycode == ARROW_DOWN || keycode == 1)
		vars->player.down = 1;
	if (keycode == ARROW_UP || keycode == 13)
		vars->player.up = 1;
	if (keycode == ARROW_LEFT)
		vars->player.aleft = 1;
	if (keycode == ARROW_RIGHT)
		vars->player.aright = 1;
	if (keycode == 0)
		vars->player.left = 1;
	if (keycode == 2)
		vars->player.right = 1;
	return (keycode);
}

static int	key_release(int keycode, t_vars *vars)
{
	if (keycode == ARROW_DOWN || keycode == 1)
		vars->player.down = 0;
	if (keycode == ARROW_UP || keycode == 13)
		vars->player.up = 0;
	if (keycode == ARROW_LEFT)
		vars->player.aleft = 0;
	if (keycode == ARROW_RIGHT)
		vars->player.aright = 0;
	if (keycode == 0)
		vars->player.left = 0;
	if (keycode == 2)
		vars->player.right = 0;
	if (keycode == 53)
		exit(0);
	return (keycode);
}

static int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	if (button == 1)
	{
		vars->player.pa -= 0.2;
		if (vars->player.pa < 0)
			vars->player.pa += PI * 2;
		vars->player.pdx = cos(vars->player.pa) * 3;
		vars->player.pdy = sin(vars->player.pa) * 3;
	}
	if (button == 2)
	{
		vars->player.pa += 0.2;
		if (vars->player.pa > 2 * PI)
			vars->player.pa -= 2 * PI;
		vars->player.pdx = cos(vars->player.pa) * 3;
		vars->player.pdy = sin(vars->player.pa) * 3;
	}
	return (0);
}

int	update(t_vars *vars)
{
	mlx_hook(vars->win, 2, 1L << 0, key_pressed, vars);
	mlx_hook(vars->win, 3, 1L << 1, key_release, vars);
	mlx_hook(vars->win, 17, 0L, xclose, vars);
	mlx_mouse_hook(vars->win, mouse_hook, vars);
	move(vars);
	drawmap(vars->mlx, vars->win, vars);
	return (1);
}
