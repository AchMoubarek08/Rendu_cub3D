/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 01:43:38 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/22 02:05:10 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	norm_angle(double angle)
{
	angle = remainder(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	move_left_right(t_vars *vars, int xo, int yo)
{
	double	new_x;
	double	new_y;

	if (vars->player.right)
	{
		new_x = vars->player.px + 3 * cos(norm_angle(vars->player.pa + M_PI_2));
		new_y = vars->player.py + 3 * sin(norm_angle(vars->player.pa + M_PI_2));
		if (wall(vars, new_x, new_y, 1) != 1)
		{
			vars->player.px = new_x;
			vars->player.py = new_y;
		}
	}
	if (vars->player.left)
	{
		new_x = vars->player.px + 3 * cos(norm_angle(vars->player.pa - M_PI_2));
		new_y = vars->player.py + 3 * sin(norm_angle(vars->player.pa - M_PI_2));
		if (wall(vars, new_x, new_y, 1) != 1)
		{
			vars->player.px = new_x;
			vars->player.py = new_y;
		}
	}
}

void	move_up_down(t_player *player, t_parse parse, int xo, int yo)
{
	if (player->down)
	{
		if (parse.map[(int)(player->py - yo) / 64][(int)player->px / 64] == 0)
			player->py -= player->pdy;
		if (parse.map[(int)player->py / 64][(int)(player->px - xo) / 64] == 0)
			player->px -= player->pdx;
	}
	if (player->up)
	{
		if (parse.map[(int)(player->py + yo) / 64][(int)player->px / 64] == 0)
			player->py += player->pdy;
		if (parse.map[(int)player->py / 64][(int)(player->px + xo) / 64] == 0)
			player->px += player->pdx;
	}
}

void	move_angle_left_right(t_player *player, int xo, int yo)
{
	if (player->aleft)
	{
		player->pa -= 0.05;
		if (player->pa < 0)
			player->pa += PI * 2;
		player->pdx = cos(player->pa) * 3;
		player->pdy = sin(player->pa) * 3;
	}
	if (player->aright)
	{
		player->pa += 0.05;
		if (player->pa > 2 * PI)
			player->pa -= 2 * PI;
		player->pdx = cos(player->pa) * 3;
		player->pdy = sin(player->pa) * 3;
	}
}

void	move(t_vars *vars)
{
	int	xo;
	int	yo;

	xo = 0;
	yo = 0;
	if (vars->player.pdx < 0)
		xo = -10;
	else
		xo = 10;
	if (vars->player.pdy < 0)
		yo = -10;
	else
		yo = 10;
	move_up_down(&vars->player, vars->parse, xo, yo);
	move_angle_left_right(&vars->player, xo, yo);
	move_left_right(vars, xo, yo);
}
