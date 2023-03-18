/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/18 15:29:18 by vhappenh         ###   ########.fr       */
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
	todo[0]->cmd = ft_calloc(sizeof(char *), 2);
	if (argc > 1)
		return (1);
	while (1)
	{
		input = readline("minishell: ");
		if (ft_strlen(input) == 4 && !ft_strncmp(input, "exit", 4))
		{
			ft_printf("%s\n", input);
			free(input);
			return (1);
		}
		add_history(input);
		todo[0]->cmd[0] = input;
		if (input_parse(todo, input))
			return (2);
		if (execute(todo, envp))
			return (3);
		free(input);
		rl_on_new_line();
	}
	ft_free(todo);
	return (0);
}
