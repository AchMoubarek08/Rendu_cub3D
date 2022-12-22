/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoubare <amoubare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 23:16:05 by amoubare          #+#    #+#             */
/*   Updated: 2022/12/19 23:26:09 by amoubare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_parse.h"

void	skip_identifiers(char **file, int *i)
{
	while (file[*i])
	{
		if (is_cellingfloor(file, *i) || is_identifier(file, *i)
			|| str_is_newline(file[*i]) || str_is_space(file[*i]))
			(*i)++;
		else
			break ;
	}
}

int	str_is_nothing(char *str)
{
	if (str[0] == '\0')
		return (1);
	return (0);
}

char	*remove_spaces(char *colors)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (colors[i] && colors[i] == 32)
		i++;
	while (colors[i] && colors[i] != 32)
	{
		colors[j] = colors[i];
		j++;
		i++;
	}
	while (colors[i])
	{
		if (colors[i] != 32)
			errors(7);
		i++;
	}
	colors[j] = '\0';
	return (0);
}

int	str_is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	in_range(char *str)
{
	int	numb;

	numb = ft_atoi(str);
	if (numb >= 0 && numb <= 255)
		return (0);
	return (1);
}
