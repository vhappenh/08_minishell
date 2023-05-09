/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:25:38 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/05 22:49:28 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static char	*ft_getdel(char *input, int *i)
{
	int		j;
	char	*del;

	while (input[(*i)] == ' ')
		(*i)++;
	j = (*i);
	while (input[j] && input[j] != ' ')
		j++;
	del = ft_strncopy(&input[(*i)], j - (*i));
	if (del == NULL)
		return (NULL);
	(*i) = j;
	return (del);
}

static char	*ft_get_docfile(int nbr)
{
	char	*doc;
	char	*str_nbr;
	char	*doc_file;

	doc = ".heredoc";
	str_nbr = ft_itoa(nbr);
	if (str_nbr == NULL)
		return (NULL);
	doc_file = ft_strjoin(doc, str_nbr);
	free(str_nbr);
	if (doc_file == NULL)
		return (NULL);
	return (doc_file);
}

static int	ft_fillfile(char *doc_file, char *del)
{
	int		fd;
	char	*new_input;

	fd = open(doc_file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd == -1)
	{
		free(del);
		return (1);
	}
	while (1)
	{
		new_input = readline("> ");
		if (new_input == NULL)
		{
			ft_putendl_fd
				("minishell: warning: here-document delimited with EOF", 2);
			return (1);
		}
		if (!ft_strncmp(del, new_input, ft_strlen(del) + 1))
		{
			free(new_input);
			break ;
		}
		write(fd, new_input, ft_strlen(new_input));
		write(fd, "\n", 1);
		free(new_input);
	}
	free(del);
	return (0);
}

static int	ft_fillit(t_cmdline **todo, char *doc_file)
{
	if ((*todo)->in_file)
	{
		if (access((*todo)->in_file, O_RDONLY) == -1)
		{
			unlink(doc_file);
			free(doc_file);
			return (0);
		}
		else
		{
			free((*todo)->in_file);
			(*todo)->in_file = doc_file;
		}
	}
	else
		(*todo)->in_file = doc_file;
	return (0);
}

int	ft_heredoc(char *input, int *i, t_cmdline **todo, int nbr)
{
	char	*del;
	char	*doc_file;

	del = ft_getdel(input, i);
	if (del == NULL)
		return (1);
	doc_file = ft_get_docfile(nbr);
	if (doc_file == NULL)
	{
		free(del);
		return (1);
	}
	if (ft_fillfile(doc_file, del))
	{
		free(doc_file);
		return (1);
	}
	return (ft_fillit(todo, doc_file));
}
