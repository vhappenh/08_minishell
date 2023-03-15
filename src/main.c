/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/15 14:35:29 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_cmdline	*todo;

	i = -1;
	if (argc > 1)
		return (1);
	while (envp[++i])
		printf("%s\n", envp[i]);
	while (1)
	{
		if (input_parse(&todo))
			return (2);
		if (pipex(todo))
			return (3);
	}
	ffree ();
	return (0);
}
