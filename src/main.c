/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/15 12:36:07 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"
/*
static void	sig_handler(int signum)
{
	if (signum == 2)
		;
	//if (signum == 3)
	//	;
}
*/
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
//		signal(SIGINT, sig_handler);
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
