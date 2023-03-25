/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/25 13:38:40 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static t_cmdline **ft_free_array(t_cmdline **todo)
{
	int	i;
	int	j;

	i = 0;
	if (todo)
	{
		while (todo[i])
		{
			if (todo[i]->in_file)
				free(todo[i]->in_file);
			if (todo[i]->out_file)
				free(todo[i]->out_file);
			if (todo[i]->cmd)
			{
				j = 0;
				while (todo[i]->cmd[j])
					free(todo[i]->cmd[j++]);
				free(todo[i]->cmd);
			}
			free(todo[i++]);
		}
		free(todo);
	}
	return (NULL);
}

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

static int	ft_fill_cmd(t_cmdline **todo, char *input, int arg_count)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	(*todo)->cmd = ft_calloc(arg_count + 1, sizeof(char *));
	if ((*todo)->cmd == NULL)
		return (1);
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
	int			arg_count;

	todo = ft_calloc(2, sizeof(t_cmdline *));
	if (todo == NULL)
		return (NULL);
	todo[0] = ft_calloc(1, sizeof(t_cmdline));
	if (todo[0] == NULL)
		return (ft_free_array(todo));
	arg_count = ft_count_args(input);
	if (ft_fill_cmd(&todo[0], input, arg_count))
		return(ft_free_array(todo));
	printf("%s.\n%s.\n", (*todo)->in_file, (*todo)->out_file);
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
