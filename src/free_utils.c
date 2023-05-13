/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 13:16:44 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/12 10:19:26 by rrupp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_free_threestr(char *str1, char *str2, char *str3)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (str3)
		free(str3);
	return (1);
}

void	ft_free_exe(pid_t *pids, int **pipe_fds, int i)
{
	int	j;

	j = 0;
	if (pipe_fds[j])
		while (j <= i)
			free(pipe_fds[j++]);
	free(pipe_fds);
	free(pids);
}

int	ft_free_lvl_fail(t_envlst **lst, t_envlst **env)
{
	free ((*lst)->evar);
	free ((*lst)->cont);
	free (*lst);
	ft_free_all(NULL, *env, NULL);
	return (0);
}

void	ft_free_close(t_cmdline *todo, char *err1, char *err2)
{
	if (todo->fd_in != 0)
		close(todo->fd_in);
	if (todo->fd_out != 1)
		close(todo->fd_out);
	ft_free_all(NULL, NULL, todo->env);
	if (err1)
	{
		perror(err1);
	}
	if (err2)
	{
		ft_putstr_fd(err2, 2);
		ft_putendl_fd(": command not found", 2);
		g_error = 127;
	}
}