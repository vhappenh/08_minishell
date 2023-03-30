/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/30 14:59:29 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static int	ft_echo(t_cmdline *todo, int fd)
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
	return (0);
}

static int	ft_pwd(int fd)
{
	char *pwd;

	pwd = ft_calloc(sizeof(char), 10000);
	if (pwd == NULL)
		return (1);
	pwd = getcwd(pwd, 9999);
	if (pwd == NULL)
	{
		perror("minishell");
		return (2);
	}
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free (pwd);
	return (0);
}

static int	ft_cd(t_cmdline *todo)
{
	char *pwd;
	char *new_path;

	pwd = ft_calloc(sizeof(char), 10000);
	if (pwd == NULL)
		return (1);
	pwd = getcwd(pwd, 9999);
	if (pwd == NULL)
	{
		perror("minishell");
		return (2);
	}
//	if (ft_strncmp(todo->cmd[1], "..", 2))
//		new_path = ft_strlcpy(pwd, todo->cmd[1]);
	new_path = ft_double_join(pwd, "/", todo->cmd[1]);
	if (new_path == NULL)
		return (3);
	free (pwd);
	if (chdir(new_path))
		return (3);
	return (0);

}

int	ft_built_in_check(t_cmdline *todo, int fd)
{
	if (!ft_strncmp(todo->cmd[0], "echo", 4))
		return (ft_echo(todo, fd));
	else if (!ft_strncmp(todo->cmd[0], "cd", 2))
		return (ft_cd(todo));
	else if (!ft_strncmp(todo->cmd[0], "pwd", 3))
		return (ft_pwd(fd));
	else if (!ft_strncmp(todo->cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(todo->cmd[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(todo->cmd[0], "env", 3))
		return (1);
	else if (!ft_strncmp(todo->cmd[0], "exit", 4))
		return (1);
	else
		return (1);
}
