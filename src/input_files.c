/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:27:11 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/17 14:27:12 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_fillinfile(t_cmdline **todo, char *input, int *i, int j)
{
	if ((*todo)->in_file || (*todo)->out_file)
	{
		if ((*todo)->in_file && access((*todo)->in_file, R_OK) == -1)
		{
			(*i) = j;
			return (0);
		}
		else if ((*todo)->out_file && access((*todo)->out_file, W_OK) == -1)
		{
			(*i) = j;
			return (0);
		}
		else
		{
			if ((*todo)->in_file && !strncmp((*todo)->in_file, ".heredoc", 8))
				unlink((*todo)->in_file);
			free((*todo)->in_file);
		}
	}
	(*todo)->in_file = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->in_file == NULL)
		return (1);
	ft_get_parse_str(input, (*todo)->in_file, i);
	return (0);
}

int	ft_get_infile(char *input, int *i, t_cmdline **todo, int nbr)
{
	int	j;

	j = (*i);
	while (input[(*i)] == '<')
		(*i)++;
	if ((*i) - j == 1)
		return (ft_heredoc(input, i, todo, nbr));
	while (input[(*i)] == ' ')
		(*i)++;
	j = ft_get_parse_len(input, (*i));
	return (ft_fillinfile(todo, input, i, j));
}

static int	ft_create(char *out_file, int trunc)
{
	int	fd;

	fd = 0;
	if (trunc)
	{
		fd = open(out_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd == -1)
			return (0);
	}
	else
	{
		fd = open(out_file, O_WRONLY | O_APPEND | O_CREAT, 0644);
		if (fd == -1)
			return (0);
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}

static int	ft_filloutfile(t_cmdline **todo, char *input, int *i)
{
	int	j;
	int	trunc;

	trunc = 0;
	j = (*i);
	while (input[(*i)] == '>')
		(*i)++;
	if ((*i) - j == 0)
		trunc = 1;
	while (input[(*i)] == ' ')
		(*i)++;
	j = ft_get_parse_len(input, (*i));
	(*todo)->out_file = ft_calloc(j - (*i) + 1, sizeof(char));
	if ((*todo)->out_file == NULL)
		return (1);
	ft_get_parse_str(input, (*todo)->out_file, i);
	if (ft_create((*todo)->out_file, trunc))
		return (1);
	return (0);
}

int	ft_get_outfile(char *input, int *i, t_cmdline **todo)
{
	if ((*todo)->in_file || (*todo)->out_file)
	{
		if ((*todo)->in_file && access((*todo)->in_file, R_OK) == -1)
		{
			while (input[(*i)] && input[(*i)] == '>')
				(*i)++;
			while (input[(*i)] && input[(*i)] == ' ')
				(*i)++;
			(*i) = ft_get_parse_len(input, (*i));
			return (0);
		}
		if ((*todo)->out_file && access((*todo)->out_file, W_OK) == -1)
		{
			while (input[(*i)] && input[(*i)] == '>')
				(*i)++;
			while (input[(*i)] && input[(*i)] == ' ')
				(*i)++;
			(*i) = ft_get_parse_len(input, (*i));
			return (0);
		}
	}
	if ((*todo)->out_file)
		free((*todo)->out_file);
	return (ft_filloutfile(todo, input, i));
}
