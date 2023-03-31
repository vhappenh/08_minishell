/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/31 14:02:52 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	static t_cmdline	**todo;
	char				**env;

	(void)argc;
	(void)argv;
	if (argc > 1)
		return (1);
	env = get_env(envp);
	if (env == NULL)
		return (2);
	while (1)
	{
		todo = input_parse();
		if (todo == NULL)
			return (2);
		if (execute(todo, env))
			return (3);
		rl_on_new_line();
	}
	ft_free_array(todo);
	return (0);
}
