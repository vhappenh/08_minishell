/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/02 16:50:34 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

// static void	ft_print_todo(t_cmdline **todo)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (todo[i])
// 	{
// 		j = -1;
// 		printf("cmd_line %ld: ", todo[i]->nbr);
// 		while (todo[i]->cmd[++j])
// 			printf("'%s' ", todo[i]->cmd[j]);
// 		printf("\n");
// 		if (todo[i]->in_file)
// 			printf("%s\n", todo[i]->in_file);
// 		if (todo[i]->out_file)
// 			printf("%s\n", todo[i]->out_file);
// 		printf("\n");
// 		i++;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	static t_cmdline	**todo;
	static t_envlst		*env;

	(void)argv;
	if (argc > 1)
		return (1);
	ft_switch_signals(INTERACTIV);
	if (get_env(envp, &env))
		return (2);
	while (1)
	{
		todo = input_parse(env);
		if (todo == NULL)
			return (errno);
		// ft_print_todo(todo);
		if (ft_execution(todo))
			return (3);
		ft_free_all(todo, NULL, NULL);
	}
	ft_free_all(NULL, env, NULL);
	return (errno);
}
