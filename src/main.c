/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/09 15:18:09 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

/*
static void	ft_print_todo(t_cmdline **todo)
{
	int	i;
	int	j;

	i = 0;
	while (todo[i])
	{
		j = -1;
		printf("cmd_line %ld: ", todo[i]->nbr);
		while (todo[i]->cmd[++j])
			printf("'%s' ", todo[i]->cmd[j]);
		printf("\n");
		if (todo[i]->in_file)
			printf("%s\n", todo[i]->in_file);
		if (todo[i]->out_file)
			printf("%s\n", todo[i]->out_file);
		printf("\n");
		i++;
	}
	ft_print_todo(todo);
}
*/

int	main(int argc, char **argv, char **envp)
{
	static t_cmdline	**todo;
	static t_envlst		*env;

	(void)argv;
	if (argc > 1)
		return (1);
	ft_switch_signals(INTERACTIV);
	if (ft_parse_env(envp, &env))
		return (1);
	while (1)
	{
		todo = input_parse(env);
		if (todo == NULL)
			return (errno);
		if (ft_execution(todo))
		{
			ft_free_all(todo, env, NULL);
			return (1); //maybe a break here could be a solution?!?!?!
		}
		ft_free_all(todo, NULL, NULL);
	}
	return (0);
}
