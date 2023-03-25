/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:27:11 by rrupp             #+#    #+#             */
/*   Updated: 2023/03/25 13:34:14 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_get_infile(char *input, int *i, t_cmdline **todo, int j)
{
	int d;

	d = 0;
	while (input[(*i)] == '<')
		(*i)++;
//	if ((*i) - j == 1)
//		ft_here_doc();
	while (input[(*i)] == ' ')
		(*i)++;
	j = (*i);
	while (input[j] && input[j] != ' ')
		j++;
	if ((*todo)->in_file)
		{
			if (access((*todo)->in_file, O_RDONLY) == -1)
				return (0);
			else
				free((*todo)->in_file);
		}
	(*todo)->in_file = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->in_file == NULL)
		return (1);
	while ((*i) < j)
		(*todo)->in_file[d++] = input[(*i)++];
	return (0);
}

int	ft_get_outfile(char *input, int *i, t_cmdline **todo, int j)
{
	int d;

	d = 0;
	if ((*todo)->out_file)
		free((*todo)->out_file);
	while (input[(*i)] == '<')
		(*i)++;
//	if ((*i) - j == 0)
//		ft_trunc();
//	else
//		ft_appand();
	while (input[(*i)] == ' ')
		(*i)++;
	j = (*i);
	while (input[j] && input[j] != ' ')
		j++;
	(*todo)->out_file = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->out_file == NULL)
		return (1);
	while ((*i) < j)
		(*todo)->out_file[d++] = input[(*i)++];
	return (0);
}
