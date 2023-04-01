/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:32:40 by vhappenh          #+#    #+#             */
/*   Updated: 2023/04/01 15:24:50 by vhappenh         ###   ########.fr       */
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
	int		new_len;
	int		i;

	(void)env;
	pwd = NULL;
	if (get_pwd(&pwd))
		return (1);
	if (!todo->cmd[1])
		new_path = ft_strdup(getenv("HOME"));
	else if (!ft_strncmp(todo->cmd[1], "..", 2))
	{
		i = -1;
		while (pwd[++i])
			if (pwd[i] == '/')
				new_len = i;
		new_path = ft_calloc(sizeof(char), new_len + 1);
		if (new_path == NULL)
			return (3);
		new_path = ft_memcpy(new_path, pwd, new_len);
		if (new_len < (int)ft_strlen(getenv("HOME")))
			new_path = ft_strdup(getenv("HOME"));
	}
	else
	{
		new_path = ft_doublejoin(pwd, "/", todo->cmd[1]);
		if (new_path == NULL)
			return (3);
/*		temp = get_env_path(env, "PWD");
		free (temp);
		env->line = ft_strdup(new_path);*/
	}
	free (pwd);
	if (chdir(new_path))
		printf("minishell: cd: %s: No such file or directory", todo->cmd[1]);
	free (new_path);
	return (0);
}

int	ft_built_in_check(t_cmdline *todo, t_envlst *env, int fd)
{
	if (!ft_strncmp(todo->cmd[0], "echo", 4))
		return (ft_echo(todo, fd));
	else if (!ft_strncmp(todo->cmd[0], "cd", 2))
		return (ft_cd(todo, env));
	else if (!ft_strncmp(todo->cmd[0], "pwd", 3))
		return (ft_pwd(fd));
	else if (!ft_strncmp(todo->cmd[0], "export", 6))
		return (1);
	else if (!ft_strncmp(todo->cmd[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(todo->cmd[0], "env", 3))
		return (ft_env(env, fd));
	else if (!ft_strncmp(todo->cmd[0], "exit", 4))
		return (1);
	else
		return (1);
}
