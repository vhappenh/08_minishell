/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:25:38 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/12 11:27:55 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

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
		return (0);
	}
	return (ft_fillit(todo, doc_file));
}
