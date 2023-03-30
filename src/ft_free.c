/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:29:17 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/30 13:17:22 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

t_cmdline	**ft_free_array(t_cmdline **todo)
{
	int	i;
	int	j;

	i = 0;
	if (todo)
	{
		while (todo[i])
		{
			if (todo[i]->in_file)
				free(todo[i]->in_file);
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
	return (NULL);
}
