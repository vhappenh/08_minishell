/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/17 12:36:10 by vhappenh         ###   ########.fr       */
/*   Updated: 2023/04/16 10:09:17 by rrupp            ###   ########.fr       */
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
static void	ft_print_todo(t_cmdline **todo)
{
	int	i;

	i = 0;
	while (todo[i])
	{
		printf("%ld\n", todo[i]->nbr);
		printf("%s\n", todo[i]->cmd[0]);
		printf("%s\n", todo[i]->in_file);
		printf("%s\n", todo[i]->out_file);
		printf("\n\n");
		i++;
	}
}

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
		ft_print_todo(todo);
		if (execute(todo, env))
			return (3);
		ft_free_all(todo, NULL, NULL);
		rl_on_new_line();
	}
	ft_free_all(NULL, env, NULL);
	return (0);
}
