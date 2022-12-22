/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:09:22 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/20 00:30:06 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

int	collect(char **file, char **map, int *i, int *j)
{
	if (is_mapline(file, *i))
	{
		while (file[*i] && is_mapline(file, *i))
		{
			map[*j] = ft_strdup(file[*i]);
			(*i)++;
			(*j)++;
		}
	}
	while (file[*i])
	{
		if ((str_is_space(file[*i]) || str_is_newline(file[*i])))
			(*i)++;
		else
			errors(8);
	}
	return (0);
}

char	**collect_map(char **file)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	j = 0;
	while (file[i])
		i++;
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	skip_identifiers(file, &i);
	while (file[i])
	{
		collect(file, map, &i, &j);
	}
	map[j] = NULL;
	return (map);
}

int	is_mapline(char **file, int i)
{
	int	j;

	j = 0;
	if (file[i][j] == '\0')
		return (0);
	while (file[i][j])
	{
		if (is_mapchar(file[i][j]))
			j++;
		else
			errors(8);
	}
	return (1);
}

int	is_mapchar(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E' || c == ' ')
		return (1);
	return (0);
}

char	**collect_identifiers(char **file)
{
	t_pvars	x;

	init_pvars(&x);
	while (file[x.i])
	{
		if (collect_iden(&x, file) == 2)
			break ;
	}
	x.tab[x.j] = NULL;
	if (x.tex != 4 || x.cf != 2)
		errors(3);
	return (x.tab);
}
