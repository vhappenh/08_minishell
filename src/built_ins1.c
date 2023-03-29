/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/29 15:09:45 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_echo(t_cmdline *todo, int fd)
{
	int	i;
	int	nl;

	i = 0;
	nl = 1;
	while (todo->cmd[++i])
	{
		if (!ft_strncmp(todo->cmd[1], "-n", 2))
			nl = 0;
		if (ft_strncmp(todo->cmd[i], "-n", 2))
		{
			if (ft_strncmp(todo->cmd[i], "-n", 2))
				ft_putstr_fd(todo->cmd[i], fd);
			if (todo->cmd[i + 1])
				write(fd, " ", 1);
		}
	}
	if (nl)
		write(fd, "\n", 1);
}

int	ft_built_in_check(t_cmdline *todo, int fd)
{
	if (!ft_strncmp(todo->cmd[0], "echo", 4))
	{
		ft_echo(todo, fd);
		return (1);
	}
	else if (!ft_strncmp(todo->cmd[0], "cd", 2))
	{
	}
	else if (!ft_strncmp(todo->cmd[0], "pwd", 3))
	{
	}
	else if (!ft_strncmp(todo->cmd[0], "export", 6))
	{
	}
	else if (!ft_strncmp(todo->cmd[0], "unset", 5))
	{
	}
	else if (!ft_strncmp(todo->cmd[0], "env", 3))
	{
	}
	else if (!ft_strncmp(todo->cmd[0], "exit", 4))
	{
	}
	return (0);
}
