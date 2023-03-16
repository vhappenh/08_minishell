/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/16 15:05:19 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	int					i;
	static t_cmdline	**todo;
	char				*input;

	(void)argc;
	(void)argv;
	i = -1;
	todo = ft_calloc(2, sizeof(t_cmdline *));
	todo[0] = malloc(sizeof(t_cmdline));
	todo[0]->cmd = ft_calloc(sizeof(char *), 4);
	todo[0]->cmd[0] = "ls";
	todo[0]->cmd[1] = "-l";
	todo[0]->cmd[2] = "-a";
	if (argc > 1)
		return (1);
	while (1)
	{
		input = readline("minishell: ");
		if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
		{
			ft_printf("%s\n", input);
			free(input);
			return (0);
		}
		add_history(input);
		if (input_parse(todo, input))
			return (2);
		free(input);
		if (execute(todo, envp))
			return (3);
		ft_free(todo);
		rl_on_new_line();
	}
	return (0);
}
