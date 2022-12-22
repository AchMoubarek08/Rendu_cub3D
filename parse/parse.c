/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:31:34 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/19 23:25:37 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

int	check_cf_colors(char *str)
{
	char	**colors;
	int		i;

	colors = ft_split(str, ',');
	i = 0;
	while (colors[i])
	{
		remove_spaces(colors[i]);
		i++;
	}
	i = 0;
	while (colors[i])
	{
		if (!str_is_digit(colors[i]) && !in_range(colors[i]))
			errors(6);
		i++;
	}
	free(str);
	ft_free_tab(colors);
	return (0);
}

int	check_iden(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		if ((tab[i][j] == 'N' && tab[i][j + 1] == 'O')
		|| (tab[i][j] == 'S' && tab[i][j + 1] == 'O')
		|| (tab[i][j] == 'W' && tab[i][j + 1] == 'E')
		|| (tab[i][j] == 'E' && tab[i][j + 1] == 'A'))
		{
			check_txt_path(ft_substr(tab[i], 2, ft_strlen(tab[i])));
		}
		else if (tab[i][j] == 'F' || tab[i][j] == 'C')
			check_cf_colors(ft_substr(tab[i], 1, ft_strlen(tab[i])));
		else
			errors(1);
		i++;
	}
	return (0);
}

int	is_cellingfloor(char **file, int i)
{
	if (ft_int_strchr(file[i], 'C') != -1)
		return (1);
	else if (ft_int_strchr(file[i], 'F') != -1)
		return (2);
	return (0);
}

int	is_identifier(char **file, int i)
{
	if (ft_int_strchr(file[i], 'N') != -1
		&& ft_int_strchr(file[i], 'O') != -1)
		return (1);
	else if (ft_int_strchr(file[i], 'S') != -1
		&& ft_int_strchr(file[i], 'O') != -1)
		return (2);
	else if (ft_int_strchr(file[i], 'W') != -1
		&& ft_int_strchr(file[i], 'E') != -1)
		return (3);
	else if (ft_int_strchr(file[i], 'E') != -1
		&& ft_int_strchr(file[i], 'A') != -1)
		return (4);
	return (0);
}

int	collect_iden(t_pvars *x, char **file)
{
	if (str_is_space(file[x->i]) || str_is_newline(file[x->i]))
	{
		(x->i)++;
		return (1);
	}
	else
	{
		if (is_identifier(file, x->i))
		{
			x->tab[x->j] = file[x->i];
			(x->tex)++;
		}
		else if (ft_int_strchr(file[x->i], ',') != -1)
		{
			x->tab[x->j] = file[x->i];
			(x->cf)++;
		}
		else if (is_mapline(file, x->i))
			return (2);
		else if (!str_is_newline(file[x->i]) && !str_is_space(file[x->i]))
			errors(3);
	}
	(x->j)++;
	(x->i)++;
	return (0);
}
