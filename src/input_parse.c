/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/28 13:49:19 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_count_args(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
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

static t_cmdline	**ft_split_input(char *input)
{
	t_cmdline	**todo;
	int			i;
	int			tokens;
	char		*token;

	i = 0;
	tokens = ft_count_token(input);
	todo = ft_calloc(tokens + 1, sizeof(t_cmdline *));
	if (todo == NULL)
		return (NULL);
	while (i < tokens)
	{
		todo[i] = ft_calloc(1, sizeof(t_cmdline));
		if (todo[i] == NULL)
			return (ft_free_array(todo));
		token = ft_get_token(input, i);
		if (token == NULL)
			return (ft_free_array(todo));
		if (ft_fill_cmd(&todo[i], token, i))
			return (ft_free_array(todo));
		free(token);
		i++;
	}
	return (todo);
}

t_cmdline	**input_parse(void)
{
	t_cmdline	**todo;
	char		*prompt;
	char		*input;

	prompt = ft_get_prompt();
	input = readline(prompt);
	if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
	{
		ft_printf("%s\n", input);
		free(input);
		free(prompt);
		return (NULL);
	}
	free(prompt);
	todo = ft_split_input(input);
	add_history(input);
	free(input);
	return (todo);
}
