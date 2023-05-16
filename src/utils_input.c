/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:54:57 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/16 15:50:43 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_get_cmd(char *input, int *i, t_cmdline **todo, int *k)
{
	int	j;
	int	d;

	j = (*i);
	while (input[j] && input[j] != ' ')
		j++;
	(*todo)->cmd[(*k)] = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->cmd[(*k)] == NULL)
		return (1);
	d = 0;
	while ((*i) < j)
	{
		if (input[(*i)] == '"' || input[(*i)] == '\'')
			(*i)++;
		else
			(*todo)->cmd[(*k)][d++] = input[(*i)++];
	}
	(*k)++;
	return (0);
}

int	ft_get_quotes(char *input, int *i, t_cmdline **todo, int *k)
{
	int		j;
	int		d;
	char	c;

	c = input[(*i)];
	(*i)++;
	j = (*i);
	d = 0;
	while (input[j] && input[j] != c)
		j++;
	// while (input[j] && input[j] != ' ')
	// 	j++;
	(*todo)->cmd[(*k)] = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->cmd[(*k)] == NULL)
		return (1);
	while ((*i) < j)
	{
		// if (input[(*i)] == '"' || input[(*i)] == '\'')
		// 	(*i)++;
		// else
			(*todo)->cmd[(*k)][d++] = input[(*i)++];
	}
	if (input[(*i)])
		(*i)++;
	(*k)++;
	return (0);
}

int	ft_get_file(char *input, int *i, t_cmdline **todo, int nbr)
{
	char	c;

	c = input[(*i)++];
	if (c == '<')
	{
		if (ft_get_infile(input, i, todo, nbr))
			return (1);
	}
	else
		if (ft_get_outfile(input, i, todo))
			return (1);
	return (0);
}
