/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:26:29 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/24 10:36:17 by rrupp            ###   ########.fr       */
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

void	ft_fill_cmd(t_cmdline **todo, char *input, int arg_count)
{
	int		i;
	int		k;

	i = 0;
	k = 0;
	(*todo)->cmd = ft_calloc(arg_count + 1, sizeof(char *));
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			ft_get_file(input, &i, todo);
		if (input[i] && (input[i] == '"' || input[i] == '\''))
			ft_get_quots(input, &i, todo, &k);
		if (input[i] && input[i] != ' ')
			ft_getcmd(input, &i, todo, &k);
		if (input[i])
			i++;
	}
}

static t_cmdline	**ft_split_input(char *input)
{
	t_cmdline	**todo;
	int			arg_count;

	todo = ft_calloc(2, sizeof(t_cmdline *));
	todo[0] = ft_calloc(1, sizeof(t_cmdline));
	arg_count = ft_count_args(input);
	ft_fill_cmd(&tt odo[0], input, arg_count);
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
