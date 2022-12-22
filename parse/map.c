/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:19:28 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/20 00:10:48 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	check_filename(char *str, int ex)
{
	int	i;
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		errors(5);
	i = 0;
	if (!strcmp(str + i, ".cub") || !strcmp(str + i, ".xpm"))
		errors(2);
	while (str[i])
	{
		if (str[i] == '.')
			break ;
		i++;
	}
	if (ex == 1)
	{
		if (strcmp(str + i, ".cub") != 0)
			errors(5);
	}
	else if (ex == 2)
	{
		if (strcmp(str + i, ".xpm") != 0)
			errors(5);
	}
}

int	check_closed(char **map, int i)
{
	int	j;

	j = 0;
	if (!map[i + 1])
		errors(9);
	while (map[i][j])
	{
		if (map[i][j] == '0')
		{
			if (!map[i][j + 1] || !map[i][j - 1])
				errors(9);
			else if (map[i][j + 1] == ' ' || map[i][j - 1] == ' ')
				errors(9);
			if (!map[i - 1][j] || !map[i + 1][j])
				errors(9);
			else if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
				errors(9);
		}
		j++;
	}
	return (0);
}

int	check_first_line(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '0')
			errors(9);
		i++;
	}
	return (0);
}

int	check_upcoming_lines(char **map, int i)
{
	i++;
	while (map[i])
	{
		if (strcmp(map[i], ""))
			errors(8);
		i++;
	}
	return (0);
}

int	check_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (strcmp(map[i], "") == 0)
			check_upcoming_lines(map, i);
		if (!is_mapline(map, i))
			errors(8);
		if (i == 0)
			check_first_line(map[i]);
		else if (there_is_zero(map, i))
			check_closed(map, i);
		i++;
	}
	return (0);
}
