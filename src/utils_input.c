/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:54:57 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/23 13:45:29 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_get_parse_len(char *input, int j)
{
	char	c;

	while (input[j] && input[j] != ' ' && input[j] != '>' && input[j] != '<')
	{
		if (input[j] == '\'' || input[j] == '"')
		{
			c = input[j++];
			while (input[j] != c)
				j++;
		}
		j++;
	}
	return (j);
}

void	ft_get_parse_str(char *input, char *dest, int *i)
{
	char	c;
	int		d;

	d = 0;
	while (input[(*i)] && input[(*i)] != ' '
		&& input[(*i)] != '<' && input[(*i)] != '>')
	{
		if (input[(*i)] == '\'' || input[(*i)] == '"')
		{
			c = input[(*i)++];
			while (input[(*i)] != c)
				dest[d++] = input[(*i)++];
			(*i)++;
		}
		else
			dest[d++] = input[(*i)++];
	}
}

int	ft_get_cmd(char *input, int *i, t_cmdline **todo, int *k)
{
	int	j;

	j = ft_get_parse_len(input, (*i));
	(*todo)->cmd[(*k)] = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->cmd[(*k)] == NULL)
		return (1);
	ft_get_parse_str(input, (*todo)->cmd[(*k)], i);
	(*k)++;
	return (0);
}

int	ft_get_quotes(char *input, int *i, t_cmdline **todo, int *k)
{
	int		j;

	j = ft_get_parse_len(input, (*i));
	(*todo)->cmd[(*k)] = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->cmd[(*k)] == NULL)
		return (1);
	ft_get_parse_str(input, (*todo)->cmd[(*k)], i);
	(*k)++;
	return (0);
}

int	ft_get_file(char *input, int *i, t_cmdline **todo, int nbr)
{
	char	c;

	c = input[(*i)];
	if (c == '<' || c == '>')
		(*i)++;
	if (c == '<')
	{
		if (ft_get_infile(input, i, todo, nbr))
			return (1);
		else
			ft_get_file(input, i, todo, nbr);
	}
	else if (c == '>')
	{
		if (ft_get_outfile(input, i, todo))
			return (1);
		else
			ft_get_file(input, i, todo, nbr);
	}
	return (0);
}
