/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 14:17:20 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/15 16:28:20 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	main(int argc, char **argv, char **envp)
{
	int			i;
	t_cmdline	*todo;

	(void)argc;
	(void)argv;
	i = -1;
	if (argc > 1)
		return (1);
	if (input_parse(&todo))
		return (2);
	if (execute(&(t_cmdline){NULL, NULL, "ls", NULL}, envp))
		return (3);
	ft_free(&todo);
	return (0);
}
