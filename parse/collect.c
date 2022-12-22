/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 00:09:26 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/21 00:50:47 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

int	fill_tab(t_parse *data, char **map, int i, int j)
{
	static int	p;

	if (map[i][j] == '0')
		data->map[i][j] = 0;
	else if (map[i][j] == '1')
		data->map[i][j] = 1;
	else if (map[i][j] == ' ')
		data->map[i][j] = 2;
	else
	{
		p++;
		data->x = j;
		data->y = i;
		if (map[i][j] == 'N')
			data->map[i][j] = 6;
		else if (map[i][j] == 'S')
			data->map[i][j] = 4;
		else if (map[i][j] == 'E')
			data->map[i][j] = 3;
		else if (map[i][j] == 'W')
			data->map[i][j] = 5;
		data->e_dir = data->map[i][j] - 3;
		data->map[i][j] = 0;
	}
	return (p);
}

void	fill_map(t_parse *data, char **map)
{
	int	i;
	int	j;
	int	p;

	i = 0;
	p = 0;
	get_height_width(data, map);
	data->map = malloc(sizeof(int *) * (data->height + 1));
	while (map[i] && is_mapline(map, i))
	{
		data->map[i] = malloc(sizeof(int) * (data->width + 1));
		j = 0;
		while (map[i][j])
			p = fill_tab(data, map, i, j++);
		while (j < data->width)
		{
			data->map[i][j] = 2;
			j++;
		}
	i++;
	}
	data->map[i] = NULL;
	if (p != 1)
		errors(10);
}

int	there_is_zero(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j])
	{
		if (map[i][j] == '0')
			return (1);
		j++;
	}
	return (0);
}
