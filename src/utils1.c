/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/18 14:14:19 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_doublejoin(char *split_path, char **path, t_cmdline **todo)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(split_path, "/");
	if (temp1 == NULL)
		return (1);
	temp2 = ft_strjoin(temp1, todo[0]->cmd[0]);
	free (temp1);
	if (temp2 == NULL)
		return (2);
	if (access(temp2, X_OK))
	{
		free (temp2);
		return (3);
	}
	*path = ft_strdup(temp2);
	free (temp2);
	return (0);
}
