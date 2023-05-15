/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:07:37 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/13 14:02:57 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

char	*ft_getdel(char *input, int *i)
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

char	*ft_get_docfile(int nbr)
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

static int	ft_readline_fillfile(char *del, int fd)
{
	char	*new_input;

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
		return (2);
	}
	ft_putendl_fd(new_input, fd);
	free(new_input);
	return (0);
}

int	ft_fillfile(char *doc_file, char *del)
{
	int	fd;
	int	destiny;

	fd = open(doc_file, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	if (fd == -1)
	{
		free(del);
		return (1);
	}
	while (1)
	{
		destiny = ft_readline_fillfile(del, fd);
		if (destiny == 1)
		{
			free(del);
			close (fd);
			return (0);
		}
		else if (destiny == 2)
			break ;
	}
	free(del);
	if (close (fd) == -1)
		return (-1);
	return (0);
}

int	ft_fillit(t_cmdline **todo, char *doc_file)
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
