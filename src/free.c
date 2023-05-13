/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:17 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/12 10:35:46 by rrupp            ###   ########.fr       */
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

static void	ft_free_cmd(t_cmdline **todo)
{
	int	i;
	int	j;

	i = 0;
	while (todo[i])
	{
		if (todo[i]->in_file)
		{
			if (!ft_strncmp(todo[i]->in_file, ".heredoc", 8))
				unlink(todo[i]->in_file);
			free(todo[i]->in_file);
		}
		if (todo[i]->out_file)
			free(todo[i]->out_file);
		if (todo[i]->cmd)
		{
			j = 0;
			while (todo[i]->cmd[j])
				free(todo[i]->cmd[j++]);
			free(todo[i]->cmd);
		}
		free(todo[i++]);
	}
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
