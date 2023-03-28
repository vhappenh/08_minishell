/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/28 11:49:45 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	static t_cmdline	**todo;

	(void)argc;
	(void)argv;
	if (argc > 1)
		return (1);
	while (1)
	{
		todo = input_parse();
		if (todo == NULL)
			return (2);
		if (execute(todo, envp))
			return (3);
		rl_on_new_line();
	}
	ft_free(todo);
	return (0);
}
