/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:54:57 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/23 17:05:14 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_getcmd(char *input, int *i, t_cmdline **todo, int *k)
{
	int	j;
	int	d;

	j = (*i);
	while (input[j] && input[j] != ' ')
		j++;
	(*todo)->cmd[(*k)] = ft_calloc(j - (*i) + 1, sizeof(char));
	d = 0;
	while ((*i) < j)
		(*todo)->cmd[(*k)][d++] = input[(*i)++];
	(*k)++;
}

void	ft_get_quots(char *input, int *i, t_cmdline **todo, int *k)
{
	int		j;
	int		d;
	char	c;

	c = input[(*i)];
	(*i)++;
	j = (*i);
	while (input[j] && input[j] != c)
		j++;
	(*todo)->cmd[(*k)] = ft_calloc(j - (*i) + 1, sizeof(char));
	d = 0;
	while ((*i) < j)
		(*todo)->cmd[(*k)][d++] = input[(*i)++];
	(*i)++;
	(*k)++;
}

void	ft_get_file(char *input, int *i, t_cmdline **todo)
{
	int		j;
	int		d;
	char	c;

	c = input[(*i)++];
	d = 0;
	while (input[(*i)] == ' ')
		(*i)++;
	j = (*i);
	while (input[j] != ' ')
		j++;
	if(c == '<')
	{
		if ((*todo)->in_file)
			free((*todo)->in_file);
		(*todo)->in_file = ft_calloc(j - (*i) + 1, sizeof(char));
		while ((*i) < j)
			(*todo)->in_file[d++] = input[(*i)++];
	}
	else
	{
		if ((*todo)->out_file)
			free((*todo)->out_file);
		(*todo)->out_file = ft_calloc(j - (*i) + 1, sizeof(char));
		while ((*i) < j)
			(*todo)->out_file[d++] = input[(*i)++];
	}
}
