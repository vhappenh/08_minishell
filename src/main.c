/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/19 09:50:06 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	int					i;
	char				*input;
	static t_cmdline	**todo;

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
		input = input_parse(todo, envp);
		if (input == NULL)
			return (2);
		todo[0]->cmd[0] = input;
		if (execute(todo, envp))
			return (3);
		free(input);
		rl_on_new_line();
	}
	ft_free(todo);
	return (0);
}
