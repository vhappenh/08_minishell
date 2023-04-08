/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/08 11:13:09 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	static t_cmdline	**todo;
	static t_envlst		*env;

	(void)argc;
	(void)argv;
	if (argc > 1)
		return (1);
	if (get_env(envp, &env))
		return (2);
	while (1)
	{
		todo = input_parse(env);
		if (todo == NULL)
			return (2);
		if (execute(todo, env))
			return (3);
		ft_free_all(todo, NULL, NULL);
		rl_on_new_line();
	}
	ft_free_all(NULL, env, NULL);
	return (0);
}
