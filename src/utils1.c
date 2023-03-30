/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/30 15:09:37 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_djoin_spec(char *split_path, char **path, t_cmdline *todo)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin(split_path, "/");
	if (temp1 == NULL)
		return (1);
	if (!todo->cmd[0])
		return (2);
	temp2 = ft_strjoin(temp1, todo->cmd[0]);
	free (temp1);
	if (temp2 == NULL)
		return (3);
	if (access(temp2, X_OK))
	{
		free (temp2);
		return (4);
	}
	*path = ft_strdup(temp2);
	free (temp2);
	return (0);
}
