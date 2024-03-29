/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/24 13:38:33 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_count_args(char *input, int i)
{
	int	count;

	count = 0;
	while (input[i])
	{
		if (input[i] && (input[i] == '<' || input[i] == '>'))
		{
			while (input[i] && input[i] == '<' && input[i] == '>')
				i++;
			while (input[i] && input[i] == ' ')
				i++;
			while (input[i] && input[i] != ' ')
				i++;
		}
		if (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>')
		{
			count++;
			while (input[i] && input[i] != ' '
				&& input[i] != '<' && input[i] != '>')
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
	(*todo)->cmd = ft_calloc(ft_count_args(input, 0) + 1, sizeof(char *));
	if ((*todo)->cmd == NULL)
		return (1);
	(*todo)->nbr = nbr;
	(*todo)->enviroment = env;
	while (input && i < (int)ft_strlen(input) - 1 && input[++i])
	{
		if (input[i] && (input[i] == '"' || input[i] == '\''))
			if (ft_get_quotes(input, &i, todo, &k))
				return (1);
		if (input[i] && input[i] != ' ' && input[i] != '<' && input[i] != '>')
			if (ft_get_cmd(input, &i, todo, &k))
				return (1);
		if (input[i] && (input[i] == '<' || input[i] == '>'))
			if (ft_get_file(input, &i, todo, nbr))
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

t_cmdline	**ft_check_prep_todo(char *input, t_envlst *env)
{
	t_cmdline	**todo;

	if (ft_check_syntax(input))
	{
		g_error = 2;
		add_history(input);
		todo = ft_calloc(1, sizeof(t_cmdline *));
		if (todo == NULL)
			return (NULL);
		return (todo);
	}
	if (ft_check_open_pipe(&input))
	{
		add_history(input);
		free(input);
		todo = ft_calloc(1, sizeof(t_cmdline *));
		return (todo);
	}
	add_history(input);
	if (ft_look_for_env(&input, env, 0))
		return (NULL);
	todo = ft_split_input(&input, env);
	free(input);
	return (todo);
}

t_cmdline	**input_parse(t_envlst *env)
{
	char	*prompt;
	char	*input;

	prompt = ft_get_prompt();
	if (prompt == NULL)
		prompt = ft_strdup("minishell: ");
	if (prompt == NULL)
		return (NULL);
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
	{
		write(1, "exit\n", 5);
		return (NULL);
	}
	return (ft_check_prep_todo(input, env));
}
