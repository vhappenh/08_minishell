/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_open_pipe.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 15:06:43 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/11 17:07:16 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_buffer_null(char *buffer, char c)
{
	if (buffer == NULL)
	{
		if (c)
		{
			ft_putstr_fd
				("minishell: unexpected EOF while looking for matching `", 2);
			ft_putchar_fd(c, 2);
			ft_putendl_fd("'", 2);
		}
		ft_putendl_fd("minishell: syntax error: unexpected end of file", 2);
		return (-1);
	}
	return (0);
}

static int	ft_get_last_cmd(char **input, int i, char c)
{
	char	*buffer;
	char	*tmp;

	buffer = readline("> ");
	if (ft_buffer_null(buffer, c))
		return (-1);
	i += ft_strlen(buffer);
	tmp = (*input);
	if (c)
	{
		(*input) = ft_doublejoin(tmp, "\n", buffer);
		free(tmp);
		free(buffer);
		if ((*input) == NULL)
			return (-1);
	}
	else
	{
		(*input) = ft_doublejoin(tmp, " ", buffer);
		free(tmp);
		free(buffer);
		if ((*input) == NULL)
			return (-1);
	}
	return (i);
}

static int	ft_check_rest(char **input)
{
	int		i;
	char	c;

	i = 0;
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
					i = ft_get_last_cmd(input, i, c);
				if (i == -1)
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
			i++;
			if (ft_get_last_cmd(input, i, 0) == -1)
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
