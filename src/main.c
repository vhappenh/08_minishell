/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/15 18:04:52 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	int					i;
	static t_cmdline	**todo;

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
	if (input_parse(todo))
		return (2);
	if (execute(todo, envp))
		return (3);
	ft_free(todo);
	return (0);
}
