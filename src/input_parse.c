/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/16 11:23:51 by rrupp            ###   ########.fr       */
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
		if (input[i] && (input[i] == '<' || input[i] == '>'))
		{
			i++;
			while (input[i] && input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ')
				i++;
		}
		if (input[i] && ft_isalpha(input[i]))
		{
			count++;
			while (input[i] && input[i] != ' ')
				i++;
		}
		if (input[i] != '\0')
			i++;
	}
	return (count);
}

static int	ft_fill_cmd(t_cmdline **todo, char *input, int nbr, t_envlst *env)
{
	int	i;
	int	k;

	i = -1;
	k = 0;
	(*todo)->cmd = ft_calloc(ft_count_args(input) + 1, sizeof(char *));
	if ((*todo)->cmd == NULL)
		return (1);
	(*todo)->nbr = nbr;
	(*todo)->enviroment = env;
	while (input && i < (int)ft_strlen(input) - 1 && input[++i])
	{
		if (input[i] && (input[i] == '<' || input[i] == '>'))
			if (ft_get_file(input, &i, todo, nbr))
				return (1);
		if (input[i] && (input[i] == '"' || input[i] == '\''))
			if (ft_get_quots(input, &i, todo, &k))
				return (1);
		if (input[i] && input[i] != ' ')
			if (ft_getcmd(input, &i, todo, &k))
				return (1);
	}
	return (0);
}

static t_cmdline	**ft_split_input(char **input, t_envlst *env)
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
		if (ft_fill_cmd(&todo[i], token, i, env))
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

t_cmdline	**input_parse(t_envlst *env)
{
	t_cmdline	**todo;
	char		*prompt;
	char		*input;

	prompt = ft_get_prompt();
	if (prompt == NULL)
		prompt = "minishell: ";
	input = readline(prompt);
	if (ft_check_syntax(input))
	{
		add_history(input);
		todo = ft_calloc(1, sizeof(t_cmdline *));
		if (todo == NULL)
			return (NULL);
		return (todo);
	}
	if (ft_check_open_pipe(&input))
		return (NULL);
	if (ft_look_for_env(&input, env))
		return (NULL);
	if (ft_strncmp(prompt, "minishell: ", sizeof(prompt)))
		free(prompt);
	todo = ft_split_input(&input, env);
	add_history(input);
	return (todo);
}
