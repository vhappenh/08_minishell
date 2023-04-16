/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/11 15:59:08 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

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
