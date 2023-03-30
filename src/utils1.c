/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrupp <rrupp@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:09:14 by vhappenh          #+#    #+#             */
/*   Updated: 2023/03/30 15:12:37 by rrupp            ###   ########.fr       */
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

char	*ft_doublejoin(char *str1, char *str2, char *str3)
{
	char	*temp;
	char	*fin;

	if (!str1 || !str2 || !str3)
		return (NULL);
	temp = ft_strjoin(str1, str2);
	if (temp == NULL)
		return (NULL);
	fin = ft_strjoin(temp, str3);
	if (fin == NULL)
	{
		free(temp);
		return (NULL);
	}
	free(temp);
	return (fin);
}
