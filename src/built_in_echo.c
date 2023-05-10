/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 11:02:13 by vhappenh          #+#    #+#             */
/*   Updated: 2023/05/10 11:49:49 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

int	ft_echo(t_cmdline *todo)
{
	int		i;
	bool	nl;

	i = 1;
	nl = true;
	if (todo->cmd[1])
	{
		if (!ft_strncmp(todo->cmd[1], "-n", 3))
		{
			nl = false;
			i++;
		}
	}
	while (todo->cmd[i])
	{
		ft_putstr_fd(todo->cmd[i], todo->fd_out);
		if (todo->cmd[i + 1])
			write(todo->fd_out, " ", 1);
		i++;
	}
	if (nl)
		write(todo->fd_out, "\n", 1);
	return (0);
}
