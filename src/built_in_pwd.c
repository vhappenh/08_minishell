/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:05 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/10 11:52:06 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_get_pwd(char **pwd)
{
	*pwd = ft_calloc(sizeof(char), 10000);
	if (*pwd == NULL)
		return (-1);
	*pwd = getcwd(*pwd, 9999);
	if (*pwd == NULL)
	{
		perror("minishell");
		return (-1);
	}
	return (0);
}

int	ft_pwd(int fd)
{
	char	*pwd;

	pwd = NULL;
	if (ft_get_pwd(&pwd))
		return (-1);
	ft_putendl_fd(pwd, fd);
	free (pwd);
	return (0);
}
