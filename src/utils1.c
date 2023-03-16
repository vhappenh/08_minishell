/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42vienna.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/16 14:37:01 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_doublejoin(char *split_path, char **path, t_cmdline **todo)
{
	char	*temp;

	temp = ft_strjoin(split_path, "/");
	if (temp == NULL)
		return (1);
	*path = ft_strjoin(temp, todo[0]->cmd[0]);
	free (temp);
	if (*path == NULL)
		return (2);
	if (access(*path, X_OK))
		return (3);
	return (0);
}
