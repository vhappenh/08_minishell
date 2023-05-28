/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:17 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/28 14:33:41 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

static void	ft_free_array(char **array)
{
	int	i;

	if (array)
	{
		i = -1;
		while (array[++i])
			free (array[i]);
		free (array);
	}
}

void	ft_free_each_cmd(t_cmdline *todo)
{
	int	j;

	if (todo)
	{
		if (todo->in_file)
		{
			if (!ft_strncmp(todo->in_file, ".heredoc", 8))
				unlink(todo->in_file);
			free(todo->in_file);
		}
		if (todo->out_file)
			free(todo->out_file);
		if (todo->cmd)
		{
			j = 0;
			while (todo->cmd[j])
				free(todo->cmd[j++]);
			free(todo->cmd);
		}
		free(todo);
	}
}

static void	ft_free_cmd(t_cmdline **todo)
{
	int	i;

	i = 0;
	while (todo[i])
		ft_free_each_cmd(todo[i++]);
	free(todo);
}

static void	ft_free_env(t_envlst *env)
{
	t_envlst	*temp;

	if (env)
	{
		while (env)
		{
			temp = env;
			if (temp->evar)
				free (temp->evar);
			if (temp->cont)
				free (temp->cont);
			env = env->next;
			free (temp);
		}
		free (env);
	}
}

void	*ft_free_all(t_cmdline **todo, t_envlst *env, char **array)
{
	if (todo)
		ft_free_cmd(todo);
	ft_free_env(env);
	ft_free_array(array);
	return (NULL);
}
