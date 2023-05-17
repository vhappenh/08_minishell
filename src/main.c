/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/17 15:38:36 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	g_error = 0;

int	main(int argc, char **argv, char **envp)
{
	static t_cmdline	**todo;
	static t_envlst		*env;

	if (argc > 1 || argv[1])
		return (1);
	ft_switch_signals(INTERACTIV);
	if (ft_parse_env(envp, &env))
		return (1);
	while (1)
	{
		todo = input_parse(env);
		if (todo == NULL)
		{
			ft_free_all(NULL, env, NULL);
			return (errno);
		}
		if (ft_execution(todo))
		{
			ft_free_all(todo, env, NULL);
			return (errno);
		}
		env = (*todo)->enviroment;
		ft_free_all(todo, NULL, NULL);
	}
	return (0);
}
