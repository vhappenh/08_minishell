/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/03 14:10:05 by vhappenh         ###   ########.fr       */
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
	static char	*pwd;

	if (get_pwd(&pwd))
		return (1);
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free (pwd);
	return (0);
}

static int	ft_cd(t_cmdline *todo, t_envlst *env)
{
	char	*pwd;
	char	*new_path;

	(void)env;
	pwd = NULL;
	if (get_pwd(&pwd))
		return (1);
	if (save_old_pwd(env, pwd))
	{
		free (pwd);
		return (2);
	}
	if (!todo->cmd[1])
	{
		new_path = ft_strdup(getenv("HOME"));
		if (new_path == NULL)
		{
			free (pwd);
			return (3);
		}
	}
	else if (!ft_strncmp(todo->cmd[1], "..", 2))
	{
		if (cd_dot_dot(pwd, &new_path))
		{
			free (pwd);
			return (4);
		}
	}
	else
	{
		new_path = ft_doublejoin(pwd, "/", todo->cmd[1]);
		if (new_path == NULL)
		{
			free (pwd);
			return (5);
		}
	}
	free (pwd);
	if (save_pwd(env, new_path))
	{
		free (new_path);
		return (6);
	}
	if (chdir(new_path))
		printf("minishell: cd: %s: No such file or directory\n", todo->cmd[1]);
	free (new_path);
	return (0);
}

int	ft_built_in_check(t_cmdline **todo, int i, t_envlst *env, int fd)
{
	if (!ft_strncmp((todo[i])->cmd[0], "echo", 4))
		return (ft_echo(todo[i], fd));
	else if (!ft_strncmp(todo[i]->cmd[0], "cd", 2))
		return (ft_cd(todo[i], env));
	else if (!ft_strncmp(todo[i]->cmd[0], "pwd", 3))
		return (ft_pwd(fd));
	else if (!ft_strncmp(todo[i]->cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(todo[i]->cmd[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(todo[i]->cmd[0], "env", 3))
		return (ft_env(env, fd));
	else if (!ft_strncmp(todo[i]->cmd[0], "exit", 4))
		return (ft_exit(todo, env));
	else
		return (1);
}
