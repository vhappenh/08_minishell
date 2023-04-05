/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/05 11:44:57 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_count_args(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input && input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ')
				i++;
		}
		if (ft_isalpha(input[i]))
		{
			count++;
			while (input[i] && input[i] != ' ')
				i++;
		}
		i++;
	}
	return (count);
}

static int	ft_fill_cmd(t_cmdline **todo, char *input, int nbr)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	(*todo)->cmd = ft_calloc(ft_count_args(input) + 1, sizeof(char *));
	if ((*todo)->cmd == NULL)
		return (1);
	(*todo)->nbr = nbr;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			if (ft_get_file(input, &i, todo))
				return (1);
		if (input[i] && (input[i] == '"' || input[i] == '\''))
			if (ft_get_quots(input, &i, todo, &k))
				return (1);
		if (input[i] && input[i] != ' ')
			if (ft_getcmd(input, &i, todo, &k))
				return (1);
		if (input[i])
			i++;
	}
	return (0);
}

static t_cmdline	**ft_split_input(char **input)
{
	t_cmdline	**todo;
	int			i;
	int			tokens;
	char		*token;

	i = 0;
	tokens = ft_count_token(*input);
	todo = ft_calloc(tokens + 1, sizeof(t_cmdline *));
	if (todo == NULL)
		return (NULL);
	while (i < tokens)
	{
		todo[i] = ft_calloc(1, sizeof(t_cmdline));
		if (todo[i] == NULL)
			return (ft_free_all(todo, NULL, NULL));
		token = ft_get_token(input, i);
		if (token == NULL)
			return (ft_free_all(todo, NULL, NULL));
		if (ft_fill_cmd(&todo[i], token, i))
			return (ft_free_all(todo, NULL, NULL));
		free(token);
		i++;
	}
	return (todo);
}

static int	ft_check_open_pipe(char **input)
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
	return (0);
}

t_cmdline	**input_parse(void)
{
	t_cmdline	**todo;
	char		*prompt;
	char		*input;

	prompt = ft_get_prompt();
	input = readline(prompt);
	if (ft_check_open_pipe(&input))
		return (NULL);
	free(prompt);
	todo = ft_split_input(&input);
	add_history(input);
	return (todo);
}
