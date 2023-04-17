/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_openin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:06:43 by rrupp             #+#    #+#             */
/*   Updated: 2023/04/17 13:43:40 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_get_last_cmd(char **input, int i)
{
	char	*buffer;
	char	*tmp;

	buffer = readline("> ");
	i += ft_strlen(buffer);
	tmp = (*input);
	(*input) = ft_strjoin(tmp, buffer);
	free(tmp);
	free(buffer);
	if ((*input) == NULL)
		return (-1);
	return (i);
}

static int	ft_check_rest(char **input)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '"' || (*input)[i] == '\'')
		{
			c = (*input)[i++];
			while ((*input)[i] != c)
			{
				while ((*input)[i] && (*input)[i] != c)
					i++;
				if ((*input)[i] == '\0')
					ft_get_last_cmd(input, j);
				if (j == -1)
					return (1);
			}
		}
		if ((*input)[i])
			i++;
	}
	return (0);
}

int	ft_check_open_pipe(char **input)
{
	int	i;

	i = 0;
	while ((*input)[i])
		i++;
	i--;
	while (i > 0)
	{
		if ((*input)[i] == '|')
		{
			i = ft_get_last_cmd(input, i);
			if (i == -1)
				return (1);
		}
		else if ((*input)[i] != ' ')
			break ;
		else
			i--;
	}
	if (ft_check_rest(input))
		return (1);
	return (0);
}
