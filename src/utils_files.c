/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:27:11 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/07 12:58:00 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_get_infile(char *input, int *i, t_cmdline **todo, int nbr)
{
	int	d;
	int	j;

	d = 0;
	j = (*i);
	while (input[(*i)] == '<')
		(*i)++;
	if ((*i) - j == 1)
	{
		if (ft_heredoc(input, i, todo, nbr))
			return (1);
		else
			return (0);
	}
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
		{
			if (strncmp((*todo)->in_file, ".heredoc", 8))
				unlink((*todo)->in_file);
			free((*todo)->in_file);
		}
	}
	(*todo)->in_file = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->in_file == NULL)
		return (1);
	while ((*i) < j)
		(*todo)->in_file[d++] = input[(*i)++];
	return (0);
}

static int	ft_create(char *out_file, int trunc)
{
	int	fd;

	fd = 0;
	if (trunc)
	{
		fd = open(out_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (1);
	}
	else
	{
		fd = open(out_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return (1);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}

int	ft_get_outfile(char *input, int *i, t_cmdline **todo)
{
	int	d;
	int	j;
	int	trunc;

	d = 0;
	trunc = 0;
	if ((*todo)->out_file)
		free((*todo)->out_file);
	while (input[(*i)] == '>')
		(*i)++;
	j = (*i);
	if ((*i) - j == 0)
		trunc = 1;
	while (input[(*i)] == ' ')
		(*i)++;
	j = (*i);
	while (input[j] != ' ')
		j++;
	(*todo)->out_file = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->out_file == NULL)
		return (1);
	while ((*i) < j)
		(*todo)->out_file[d++] = input[(*i)++];
	if (ft_create((*todo)->out_file, trunc))
		return (1);
	return (0);
}
