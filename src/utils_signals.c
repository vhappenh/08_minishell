/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhappenh <vhappenh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 09:58:05 by rrupp             #+#    #+#             */
/*   Updated: 2023/05/05 09:35:33 by vhappenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vr.h"

void	ft_handle_inter(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		errno = 130;
	}
}

void	ft_handle_exe(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
	}
}

int	ft_switch_signals(int sig_case)
{
	static struct sigaction	sa;

	if (sig_case == INTERACTIV)
	{
		sa.sa_handler = &ft_handle_inter;
		if (sigaction(SIGINT, &sa, NULL))
			return (1);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_case == EXECUTING)
	{
		sa.sa_handler = &ft_handle_exe;
		if (sigaction(SIGINT, &sa, NULL))
			return (1);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig_case == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	return (0);
}
