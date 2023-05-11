/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/11 10:59:11 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

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
			return (1);
		}
		ft_free_all(todo, NULL, NULL);
	}
	return (0);
}
