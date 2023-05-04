/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:05:05 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/04 11:53:27 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_pwd(int fd)
{
	static char	*pwd;

	if (ft_get_pwd(&pwd))
		return (1);
	ft_putstr_fd(pwd, fd);
	write(fd, "\n", 1);
	free (pwd);
	return (0);
}